#include "s21_grep.h"

/* --- Функция, main --- */
int main(int argc, char** argv) {
    char pattern[BUFFSIZE] = {0};

    init_options();
    if (argc > 1) {
        parse_option(argc, argv, pattern);
        open_file(argc, argv, pattern);
    } else {
        printf(ERRMESSAGE);
    }
    return (0);
}

/* --- Функция инициализации опций --- */
void init_options() {
    opt.e = false;
    opt.i = false;
    opt.v = false;
    opt.c = false;
    opt.l = false;
    opt.n = false;
    opt.h = false;
    opt.s = false;
    opt.f = false;
    opt.o = false;
    opt.files_count = 0;
    opt.empty_line = 0;
}

/* --- Функция для (-e) флага --- */
void e_process(int* e_count, char* pattern) {
    if (*e_count) {
        strcat(pattern, "|");
    }
    if (!*optarg) {
        optarg = ".";
        opt.empty_line += 1;
    }
    strcat(pattern, optarg);
    *e_count += 1;
}

/* --- Функция для (-f) флага --- */
void f_process(int* e_count, char* pattern) {
    FILE* fp = NULL;
    char line[BUFFSIZE] = {0};

    if ((fp = fopen(optarg, "r"))) {
        fseek(fp, 0, SEEK_SET);
        while (fgets(line, BUFFSIZE, fp) != NULL) {
            if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
            if (*e_count > 0) strcat(pattern, "|");
            if (*line == '\0') {
                opt.empty_line = 1;
                strcat(pattern, ".");
            } else {
                strcat(pattern, line);
            }
            *e_count += 1;
        }
        fclose(fp);
    } else {
        printf("s21_grep: %s: No such file\n", optarg);
        exit(1);
    }
}

/* --- Функция парсинга опций (флагов) --- */
void parse_option(int argc, char** argv, char* pattern) {
    int option, e_count = 0;
    const char* optstring = "e:f:ivclnhso";

    while (true) {
        option = getopt_long(argc, argv, optstring, NULL, NULL);
        if (option == -1) break;
        switch (option) {
            case 'e':
                opt.e = true;
                e_process(&e_count, pattern);
                break;
            case 'i':
                opt.i = true;
                break;
            case 'v':
                opt.v = true;
                break;
            case 'c':
                opt.c = true;
                break;
            case 'l':
                opt.l = true;
                break;
            case 'n':
                opt.n = true;
                break;
            case 'h':
                opt.h = true;
                break;
            case 's':
                opt.s = true;
                break;
            case 'f':
                opt.f = true;
                f_process(&e_count, pattern);
                break;
            case 'o':
                opt.o = true;
                break;
            default:
                exit(1);
        }
    }
    if (opt.empty_line) opt.o = 0;
    if (!opt.e && !opt.f) {
        if (!*argv[optind]) argv[optind] = ".";
        strcat(pattern, argv[optind]);
        optind += 1;
    }
}

/* --- Функция открытия файлов --- */
void open_file(int argc, char** argv, char* pattern) {
    opt.files_count = argc - optind;

    for (; optind < argc; optind++) {
        FILE* steam;
        if ((steam = fopen(argv[optind], "r")) != NULL) {
            output(argv, pattern, steam);
            fclose(steam);
        } else {
            if (!opt.s)
                printf("s21_grep: %s: No such file or directory\n",
                       argv[optind]);
        }
    }
}

void output(char** argv, char* pattern, FILE* steam) {
    regex_t regex;  // структура для регулярного выражения
    int success = 0;  // результат работы regex (default=0)
    int regflag = REG_EXTENDED;
    char str[BUFFSIZE] = {0};  // временная строка (tmp)
    size_t line_number = 1;

    int lines_count = 0;
    regmatch_t pmatch[1] = {0};
    size_t nmatch = 1;

    if (opt.i) regflag |= REG_ICASE;

    // готовит бинарник регулярного выражения
    regcomp(&regex, pattern, regflag);

    while (!feof(steam)) {
        if (fgets(str, BUFFSIZE, steam)) {
            int new_line_o_counter = 1;
            success = regexec(&regex, str, nmatch, pmatch, 0);
            if (opt.v) success = success ? 0 : 1;

            if (success != REG_NOMATCH) {
                if (!opt.c && !opt.l) {
                    if (opt.files_count > 1 && !opt.h) {
                        printf("%s:", argv[optind]);
                    }
                    if (opt.n) {
                        printf("%lu:", line_number);
                    }
                    if (opt.o && !opt.v) {
                        new_line_o_counter = 0;
                        char* ptr = str;
                        while (!success) {
                            if (pmatch[0].rm_eo == pmatch[0].rm_so) break;
                            printf("%.*s\n",
                                   (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
                                   ptr + pmatch[0].rm_so);
                            ptr += pmatch[0].rm_eo;
                            success = regexec(&regex, ptr, nmatch, pmatch,
                                              REG_NOTBOL);
                        }
                    }

                    if (!opt.o) printf("%s", str);
                    if (str[strlen(str) - 1] != '\n' && new_line_o_counter) {
                        printf("\n");
                    }
                }
                lines_count += 1;
            }

            line_number += 1;
        }
    }

    if (opt.c) {
        if (opt.files_count > 1 && !opt.h) {
            printf("%s:", argv[optind]);
        }
        if (opt.l && lines_count)
            printf("1\n");
        else
            printf("%d\n", lines_count);
    }

    if (opt.l && lines_count) {
        printf("%s\n", argv[optind]);
    }
    regfree(&regex);
}
