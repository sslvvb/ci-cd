#include "s21_grep.h"

int main(int argc, char* argv[]) {
  int return_value = 0;
  int file_count;
  opt_list opt = {0};
  is_i_exist(argc, argv, &opt);
  char template[4096] = {0};
  template[0] = '(';
  file_count = check_opt(argc, argv, &opt, template);
  if (file_count >= 0) {
    int template_index = 0;
    if (opt.e == 0) {
      template[0] = '\0';
      if (opt.i != 0) {
        i_process(find_pattern(argc, argv, &template_index), 0, template, 0);
      } else {
        strcat(template, find_pattern(argc, argv, &template_index));
        file_count -= 1;
      }
    }
    file_open(argc, argv, opt, template, file_count, template_index);
  }
  return return_value;
}

void is_i_exist(int argc, char* argv[], opt_list* opt) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (int j = 0; argv[i][j] != '\0'; j++) {
        if (argv[i][j] == 'i') {
          opt->i = 1;
        }
      }
    }
  }
}

int check_opt(int argc, char* argv[], opt_list* opt, char* template) {
  int file_count = 0;
  int flag_error;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-') {
      flag_error = opt_process(argv, &i, opt, template);
      if (flag_error) {
        file_count = -1;
        break;
      }
    } else {
      file_count += 1;
    }
  }
  int len = strlen(template);
  if (len!= 1)
    template[len] = ')';
  return file_count;
}

int opt_process(char* argv[], int* i, opt_list* opt, char* template) {
  int return_value = 0;
  int flag_e = 0;
  int len = strlen(argv[*i]);
  for (int j = 1; j < len && !return_value && !flag_e; j++) {
    switch (argv[*i][j]) {
      case 'e':
        opt->e += 1;
        return_value = collect_template(argv, template, i, j, opt);
        flag_e = 1;
        break;
      case 'i': break;
      case 'v': opt->v += 1; break;
      case 'c': opt->c += 1; break;
      case 'l': opt->l += 1; break;
      case 'n': opt->n += 1; break;
      case 'h': opt->h += 1; break;
      case 's': opt->s += 1; break;
      case 'o': opt->o += 1; break;
      default:
        return_value = 1;
        if (opt->s == 0)
          fprintf(stderr, "s21_grep: invalid option -- %c\n" ERROR_USAGE "\n", argv[*i][j]);
        break;
    }
  }
  return return_value;
}

int collect_template(char* argv[], char* template, int* i, int j, opt_list* opt) {
  int return_value = 0;
  int n = strlen(template);
  if (n != 1) {
    template[n++] = '|';
  }
  if (argv[*i][++j] != '\0') {
    if (opt->i > 0) {
      i_process(argv[*i], j, template, n);
    } else {
      for (; argv[*i][j] != '\0'; n++, j++)
        template[n] = argv[*i][j];
    }
  } else {
    j = 0;
    if (argv[*i] != NULL) {
      *i += 1;
      if (opt->i > 0) {
        i_process(argv[*i], j, template, n);
      } else {
        template[n] = '(';
        strcat(template, argv[*i]);
        n = strlen(template);
        template[n] = ')';
      }
    } else {
      return_value = 2;
    }
  }
  return return_value;
}

void i_process(char* src, int i, char* template, int n) {
  template[n++] = '(';
  int len = strlen(&src[i]);
  for (int q = 0; q < len; q++) {
    char c, tmp;
    c = src[i];
    tmp = toupper(c);
    if (tmp == c)
      tmp = tolower(c);
    template[n++] = '(';
    for (int src_i = i; src_i < (i + 1); ++src_i) {
      template[n++] = src[src_i];
    }
    template[n++] = '|';
    template[n] = tmp;
    n += 1;
    template[n++] = ')';
    i += 1;
  }
  template[n] = ')';
}

char* find_pattern(int argc, char* argv[], int* template_index) {
  char* return_value = NULL;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      return_value = &argv[i][0];
      *template_index = i;
      break;
    }
  }
  return return_value;
}

void file_open(int argc, char* argv[], opt_list opt, char* template, int file_count, int template_index) {
  FILE* fp;
  char file_name[256] = {0};
  for (int i = template_index + 1; i < argc; i++) {
    if (argv[i][0] != '-' && e_check(argv[i - 1])) {
      if ((fp = fopen(&argv[i][0], "r")) != NULL) {
        if (((file_count > 1) && opt.h == 0) || opt.l != 0) {
          strcpy(file_name, argv[i]);
          if (opt.l == 0)
            strcat(file_name, ":");
        }
        int cnt = print_file(fp, file_name, opt, template);
        if (opt.l != 0) {
          printf("%s\n", file_name);
        } else if (opt.c != 0) {
          printf("%s%d\n", file_name, cnt);
        }
        fclose(fp);
      } else {
        if (opt.s == 0)
          fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[i]);
      }
    }
  }
}

int e_check(char* str) {
  int return_value = 1;
  if (str[0] == '-') {
    int len = strlen(str);
    if (str[len - 1] == 'e')
      return_value = 0;
  }
  return return_value;
}

int print_file(FILE* fp, char* file_name, opt_list opt, char* template) {
  regex_t regex;
  regmatch_t pm;
  regcomp(&regex, template, REG_EXTENDED);
  int line_number = 1;
  int cnt = 0;
  char str[1024] = {0};
  while (s21_fgets(str, fp) != 0) {
    if (opt.o != 0 && opt.c == 0) {
      long long int shift = 0;
      while (1) {
        int result = regexec(&regex, &str[shift], 1, &pm, 0);
        if (result == 0) {
          if (opt.l == 0) {
            printf("%s", file_name);
            if (opt.n != 0)
              printf("%d:", line_number);
            for (unsigned int i = pm.rm_so + shift; i < pm.rm_eo + shift; i++) {
              printf("%c", str[i]);
            }
            printf("\n");
          }
          shift += pm.rm_eo;
        } else {
          break;
        }
      }
    } else {
      cnt = zero_o_process(regex, pm, str, opt, file_name, line_number, cnt);
    }
    line_number += 1;
  }
  regfree(&regex);
  return cnt;
}

int zero_o_process(regex_t regex, regmatch_t pm, char* str, opt_list opt, char* file_name,
                                                                int line_number, int cnt) {
  int count = cnt;
  int result = regexec(&regex, str, 1, &pm, 0);
  if (opt.v != 0)
    result = !result;
  if (result == 0) {
    if (opt.c == 0 && opt.l == 0) {
      if (opt.n != 0)
        printf("%d:", line_number);
      printf("%s\n", str);
    }
    ++count;
  }
return count;
}

int s21_fgets(char* str, FILE *fp) {
  int return_value = 1;
  int i = 0;
  int sym;
  while (1) {
    sym = fgetc(fp);
    if (sym == '\n' || sym == EOF) {
      str[i] = '\0';
      break;
    }
    str[i] = (char)sym;
    i += 1;
  }
  if (sym == EOF && i == 0)
    return_value = 0;
  return return_value;
}
