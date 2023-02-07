#include "s21_cat.h"

int main(int argc, char** argv) {
    init_option();
    parse_option(argc, argv);
    print_file(argc, argv);
    return 0;
}

void init_option() {
    opt.b = false;
    opt.e = false;
    opt.v = false;
    opt.s = false;
    opt.t = false;
    opt.n = false;
}

void parse_option(int n, char** str) {
    int option;
    int option_index = 0;
    const char* optstring = "+beEnstT";

    opterr = 0;
    while (true) {
        option = getopt_long(n, str, optstring, long_options, &option_index);
        if (option == -1) break;
        switch (option) {
            case 0:
                if (strcmp(long_options[option_index].name,
                           "number-nonblank") == 0)
                    opt.b = true;
                if (strcmp(long_options[option_index].name, "number") == 0)
                    opt.n = true;
                if (strcmp(long_options[option_index].name, "squeeze-blank") ==
                    0)
                    opt.s = true;
                break;
            case 'b':
                opt.b = true;
                break;
            case 'e':
                opt.v = true;
                opt.e = true;
                break;
            case 'E':
                opt.e = true;
                break;
            case 's':
                opt.s = true;
                break;
            case 't':
                opt.v = true;
                opt.t = true;
                break;
            case 'T':
                opt.t = true;
                break;
            case 'n':
                opt.n = true;
                break;
            default:
                printf("s21_cat: illegal option -- %s\n", str[optind - 1] + 1);
                printf("usage: s21_cat [-beEnstT] [file ...]\n");
                exit(1);
        }
    }
    if (opt.b) opt.n = false;
}

void print_file(int n, char** str) {
    int c = 0;
    size_t line_number = 1;
    size_t empty_line_flag = 0;
    bool new_line = true;

    for (int i = optind; i < n; i++) {
        FILE* steam = fopen(str[i], "r");
        if (steam == NULL) {
            printf("s21_cat: %s: No such file or directory\n", str[i]);
            continue;
        }
        while ((c = fgetc(steam)) != EOF) {
            if (opt.s) {
                if (c == '\n') {
                    empty_line_flag += 1;
                    if (empty_line_flag > 2) {
                        continue;
                    }
                } else {
                    empty_line_flag = 0;
                }
            }
            if (opt.n && new_line) {
                printf("%6ld\t", line_number);
                line_number += 1;
                new_line = false;
            }
            if (opt.b && new_line && c != '\n') {
                printf("%6ld\t", line_number);
                line_number += 1;
                new_line = false;
            }
            if (opt.t && c == '\t') {
                printf("^");
                c = 'I';
            }
            if (opt.v && c != '\n' && c != '\t') {
                if (c >= 0 && c <= 31) {
                    printf("^");
                    c += 64;
                } else if (c == 127) {
                    printf("^");
                    c -= 64;
                }
            }
            if (opt.e && c == '\n') {
                printf("$");
            }
            if (c == '\n') {
                new_line = true;
            }
            printf("%c", c);
        }
        fclose(steam);
    }
}
