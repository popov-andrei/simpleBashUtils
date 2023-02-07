#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <string.h> /* for strcmp */

#define BUFFSIZE 8192
#define ERRMESSAGE                                                          \
    "usage: s21_grep [-eivclnhsfo] [-e pattern] [-f file] [pattern] [file " \
    "...]\n"

struct Options {
    bool e, i, v, c, l, n, h, s, f, o;
    int files_count;
    int empty_line;
} opt;

void init_options();
void parse_option(int argc, char** argv, char* pattern);
void open_file(int argc, char** argv, char* pattern);
void e_process(int* e_count, char* pattern);
void f_process(int* e_count, char* pattern);
void output(char** argv, char* pattern, FILE* steam);

#endif  // SRC_GREP_S21_GREP_H_
