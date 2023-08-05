CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11

all: s21_grep test

s21_grep: 
	$(CC) s21_grep.c $(FLAGC) -o s21_grep

test:
	sh ./test.sh

clean:
	rm s21_grep
	rm s21_grep.txt
	rm grep.txt

linter:
	python3 ../../materials/linters/cpplint.py --extensions=c ./s21_grep.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./s21_grep.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./s21_grep.c
