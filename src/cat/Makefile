CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11

all: s21_cat test

s21_cat: 
	$(CC) s21_cat.c $(FLAGC) -o s21_cat

test:
	rm -rf *.txt
	sh ./test.sh

clean:
	rm -f s21_cat *.txt

linter:
	python3 ../../materials/linters/cpplint.py --extensions=c ./s21_cat.c
	python3 ../../materials/linters/cpplint.py --extensions=c ./s21_cat.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./s21_cat.c
