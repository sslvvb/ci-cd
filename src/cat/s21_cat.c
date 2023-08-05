#include "s21_cat.h"

int main(int argc, char* argv[]) {
    int return_value = 0;
    if (argc > 1) {
        opt_list opt = {0};
        int find_file = 0;
        for (int i = 1; i < argc && return_value == 0; i++) {
            if (find_file == 0 && argv[i][0] == '-') {
                return_value = arg_process(argc, argv, &opt, i);
            } else if ((find_file == 0 && argv[i][0] != '-') ||
                                                find_file == 1) {
                find_file = 1;
                open_file(argv[i], opt);
            }
        }
    } else {
        return_value = 1;
    }
    return return_value;
}

int arg_process(int argc, char* argv[], opt_list *opt, int i) {
    int return_value = 0;
    if (argv[i][0] == '-' && argv[i][1] != '-') {
        return_value = opt_process(argv, i, opt);
    } else if (argv[i][0] == '-' && argv[i][1] == '-') {
        return_value = opt_long_process(argv, i, opt);
    }
    return return_value;
}

int opt_process(char* argv[], int i, opt_list *opt) {
    int return_value = 0;
    for (int j = 1; j < strlen(argv[i]); j++) {
        switch (argv[i][j]) {
            case 'b': opt->b = 1; break;
            case 'e': opt->e = 1; opt->v = 1; break;
            case 'E': opt->e = 1; break;
            case 'n': opt->n = 1; break;
            case 's': opt->s = 1; break;
            case 't': opt->t = 1; opt->v = 1; break;
            case 'T': opt->t = 1; break;
            case 'v': opt->v = 1; break;
            default:
                return_value = 1;
                fprintf(stderr, "cat: illegal option -- %c\n"
                "usage: cat [-benstv] [file ...]\n", argv[i][j]);
                break;
        }
    }
    return return_value;
}

int opt_long_process(char* argv[], int i, opt_list *opt) {
    int return_value = 0;
    if (strcmp(argv[i], "--number-nonblank") == 0) {
        opt->b = 1;
    } else if (strcmp(argv[i], "--number") == 0) {
        opt->n = 1;
    } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        opt->s = 1;
    } else {
        return_value = 1;
        fprintf(stderr, "cat: unrecognized option '%s'\n"
        "Try 'cat --help' for more information.\n", &argv[i][0]);
    }
    return return_value;
}

void open_file(char* argv, opt_list opt) {
    FILE* fp = NULL;
    fp = fopen(argv, "r");
    if (fp != NULL) {
        print_file(fp, opt);
        fclose(fp);
    } else {
        printf("s21_cat: %s: No such file or directory\n", argv);
    }
}

void print_file(FILE* fp, opt_list opt) {
    int symbol;
    int newline = 1;
    int num_line = 1;
    int skip_symbol = 0;
    char symbol_prev_line = 'c';
    while ((symbol = getc(fp)) != EOF) {
        if (opt.b != 0 && newline == 1 && symbol != '\n') {
            printf("%6d\t", num_line);
            num_line += 1;
        }
        if (opt.s != 0 && newline == 1 && symbol_prev_line == '\n' &&
                                                        symbol == '\n') {
            skip_symbol = 1;
        }
        if (opt.n != 0 && opt.b == 0 && newline == 1 && skip_symbol == 0) {
            printf("%6d\t", num_line);
            num_line += 1;
        }
        if (opt.v != 0) {
            convert(&symbol, &num_line, &skip_symbol, opt);
        }
        if (opt.e != 0 && symbol == '\n' && skip_symbol == 0) {
            printf("$");
        }
        if (opt.t != 0 && symbol == '\t') {
            printf("^I");
            skip_symbol = 1;
        }
        if (skip_symbol == 0) {
            printf("%c", symbol);
        } else {
            skip_symbol = 0;
        }
        if (newline == 1) {
            symbol_prev_line = symbol;
        }
        if (newline == 1 && symbol != '\n') {
            newline = 0;
        }
        if (newline == 0 && symbol == '\n') {
            newline = 1;
        }
    }
}

void convert(int* symbol, int* num_line, int* skip_symbol, opt_list opt) {
    if (*symbol >= 0 && *symbol < 32 && *symbol != 9 && *symbol != 10) {
        printf("^");
        *symbol += 64;
    } else if (*symbol == 127) {
        printf("^");
        *symbol -= 64;
    } else if (*symbol >= 128 && *symbol <= 159) {
        printf("M-");
        if ((opt.b != 0 ||opt.n != 0) && *symbol == 138) {
            printf("J%6d\t", *num_line);
            *num_line += 1;
            *skip_symbol = 1;
        }
        *symbol -= 64;
    } else if (*symbol > 159 && *symbol != 255) {
        printf("M-");
        *symbol -= 128;
    } else if (*symbol == 255) {
        printf("M-^");
        *symbol -= 192;
    }
}
