#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define ERROR_USAGE "usage: s21_grep [-ivclnhs] [-e pattern] [pattern] [file ...]"

#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

typedef struct OPT {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
} opt_list;

void is_i_exist(int argc, char* argv[], opt_list* opt);
int check_opt(int argc, char* argv[], opt_list* opt, char* template);
int opt_process(char* argv[], int* i, opt_list* opt, char* template);
int collect_template(char* argv[], char* template, int* i, int j, opt_list* opt);
void i_process(char* src, int i, char* template, int n);
char* find_pattern(int argc, char* argv[], int* template_index);
void file_open(int argc, char* argv[], opt_list opt, char* template, int file_count, int template_index);
int e_check(char* str);
int print_file(FILE* fp, char* file_name, opt_list opt, char* template);
int zero_o_process(regex_t regex, regmatch_t pm, char* str, opt_list opt, char* file_name,
                                                                int line_number, int cnt);
int s21_fgets(char* str, FILE *fp);

#endif  // SRC_GREP_S21_GREP_H_
