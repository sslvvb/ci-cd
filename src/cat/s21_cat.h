#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct OPT {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt_list;

int arg_process(int argc, char* argv[], opt_list* opt, int i);
int opt_process(char* argv[], int i, opt_list* opt);
int opt_long_process(char* argv[], int i, opt_list* opt);
void open_file(char* argv, opt_list opt);
void print_file(FILE* fp, opt_list opt);
void convert(int* symbol, int* num_line, int* skip_symbol, opt_list opt);

#endif  // SRC_CAT_S21_CAT_H_
