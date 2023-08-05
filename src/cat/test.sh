#!/bin/bash

FILE="s21_cat.c"
FILE1="s21_cat.h"

########## TEST 1 ##########

./s21_cat $FILE >> s21_cat.txt
./s21_cat -b $FILE >> s21_cat.txt
./s21_cat -n $FILE >> s21_cat.txt
./s21_cat -s $FILE >> s21_cat.txt
./s21_cat -e $FILE >> s21_cat.txt
./s21_cat -t $FILE >> s21_cat.txt
./s21_cat -v $FILE >> s21_cat.txt

cat $FILE >> cat.txt
cat -b $FILE >> cat.txt
cat -n $FILE >> cat.txt
cat -s $FILE >> cat.txt
cat -e $FILE >> cat.txt
cat -t $FILE >> cat.txt
cat -v $FILE >> cat.txt

########## TEST 2 ##########

./s21_cat -bn $FILE >> s21_cat.txt
./s21_cat -bs $FILE >> s21_cat.txt
./s21_cat -bt $FILE >> s21_cat.txt
./s21_cat -bv $FILE >> s21_cat.txt
./s21_cat -ns $FILE >> s21_cat.txt
./s21_cat -nt $FILE >> s21_cat.txt
./s21_cat -nv $FILE >> s21_cat.txt
./s21_cat -ne $FILE >> s21_cat.txt
./s21_cat -st $FILE >> s21_cat.txt
./s21_cat -sv $FILE >> s21_cat.txt
./s21_cat -se $FILE >> s21_cat.txt
./s21_cat -tv $FILE >> s21_cat.txt
./s21_cat -te $FILE >> s21_cat.txt

cat -bn $FILE >> cat.txt
cat -bs $FILE >> cat.txt
cat -bt $FILE >> cat.txt
cat -bv $FILE >> cat.txt
cat -ns $FILE >> cat.txt
cat -nt $FILE >> cat.txt
cat -nv $FILE >> cat.txt
cat -ne $FILE >> cat.txt
cat -st $FILE >> cat.txt
cat -sv $FILE >> cat.txt
cat -se $FILE >> cat.txt
cat -tv $FILE >> cat.txt
cat -te $FILE >> cat.txt

########## TEST 3 ##########

./s21_cat -bbbb $FILE >> s21_cat.txt
./s21_cat -nnnn $FILE >> s21_cat.txt
./s21_cat -ssss $FILE >> s21_cat.txt
./s21_cat -eeee $FILE >> s21_cat.txt
./s21_cat -tttt $FILE >> s21_cat.txt
./s21_cat -vvvv $FILE >> s21_cat.txt

cat -bbbb $FILE >> cat.txt
cat -nnnn $FILE >> cat.txt
cat -ssss $FILE >> cat.txt
cat -eeee $FILE >> cat.txt
cat -tttt $FILE >> cat.txt
cat -vvvv $FILE >> cat.txt

diff -s s21_cat.txt cat.txt
