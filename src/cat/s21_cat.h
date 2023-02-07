#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> /* for exit */
#include <string.h> /* for strcmp */

struct opt {
    bool b;
    bool e;
    bool v;
    bool s;
    bool t;
    bool n;
} opt;

static struct option long_options[] = {{"number-nonblank", no_argument, 0, 0},
                                       {"number", no_argument, 0, 0},
                                       {"squeeze-blank", no_argument, 0, 0},
                                       {0, 0, 0, 0}};

void init_option();
void parse_option(int n, char** str);
void print_file(int n, char** str);

#endif  // SRC_CAT_S21_CAT_H_
