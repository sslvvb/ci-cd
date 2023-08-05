#!/bin/bash

PATTERN="cat"
PATTERN1="oo"
FILE="1.txt"
FILE1="2.txt"

########## TEST 1 ##########

./s21_grep $PATTERN $FILE >> s21_grep.txt
./s21_grep -e $PATTERN $FILE >> s21_grep.txt
./s21_grep -e $PATTERN -e $PATTERN1 $FILE >> s21_grep.txt
./s21_grep -e $PATTERN $FILE -e $PATTERN1>> s21_grep.txt
./s21_grep -i $PATTERN $FILE >> s21_grep.txt
./s21_grep -v $PATTERN $FILE >> s21_grep.txt
./s21_grep -c $PATTERN $FILE >> s21_grep.txt
./s21_grep -l $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -n $PATTERN $FILE >> s21_grep.txt
./s21_grep -h $PATTERN $FILE >> s21_grep.txt
./s21_grep -s $PATTERN $FILE >> s21_grep.txt
./s21_grep -o $PATTERN $FILE >> s21_grep.txt
./s21_grep -o $PATTERN $FILE $FILE1 >> s21_grep.txt

########## TEST 2 ##########

./s21_grep -ce $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -le $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -c -e $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -ic $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -il $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -ln $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -lo $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -le $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -oe $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -ih $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -hs $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -ho $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -io $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -vc $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -cn $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -nh $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -no $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -co $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -ch $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -so $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -vl $PATTERN $FILE $FILE1 $FILE1 >> s21_grep.txt
./s21_grep -ich $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -lne $PATTERN $FILE $FILE1 >> s21_grep.txt
./s21_grep -hso $PATTERN $FILE $FILE1 >> s21_grep.txt

########## TEST 1.1 ##########

grep $PATTERN $FILE >> grep.txt
grep -e $PATTERN $FILE >> grep.txt
grep -e $PATTERN -e $PATTERN1 $FILE >> grep.txt
grep -e $PATTERN $FILE -e $PATTERN1 >> grep.txt
grep -i $PATTERN $FILE >> grep.txt
grep -v $PATTERN $FILE >> grep.txt
grep -c $PATTERN $FILE >> grep.txt
grep -l $PATTERN $FILE $FILE1 >> grep.txt
grep -n $PATTERN $FILE >> grep.txt
grep -h $PATTERN $FILE >> grep.txt
grep -s $PATTERN $FILE >> grep.txt
grep -o $PATTERN $FILE >> grep.txt
grep -o $PATTERN $FILE $FILE1 >> grep.txt

########## TEST 2.1 ##########

grep -ce $PATTERN $FILE $FILE1 >> grep.txt
grep -le $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -c -e $PATTERN $FILE $FILE1 >> grep.txt
grep -ic $PATTERN $FILE $FILE1 >> grep.txt
grep -il $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -ln $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -lo $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -le $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -oe $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -ih $PATTERN $FILE $FILE1 >> grep.txt
grep -hs $PATTERN $FILE $FILE1 >> grep.txt
grep -ho $PATTERN $FILE $FILE1 >> grep.txt
grep -io $PATTERN $FILE $FILE1 >> grep.txt
grep -vc $PATTERN $FILE $FILE1 >> grep.txt
grep -cn $PATTERN $FILE $FILE1 >> grep.txt
grep -nh $PATTERN $FILE $FILE1 >> grep.txt
grep -no $PATTERN $FILE $FILE1 >> grep.txt
grep -co $PATTERN $FILE $FILE1 >> grep.txt
grep -ch $PATTERN $FILE $FILE1 >> grep.txt
grep -so $PATTERN $FILE $FILE1 >> grep.txt
grep -vl $PATTERN $FILE $FILE1 $FILE1 >> grep.txt
grep -ich $PATTERN $FILE $FILE1 >> grep.txt
grep -lne $PATTERN $FILE $FILE1 >> grep.txt
grep -hso $PATTERN $FILE $FILE1 >> grep.txt

diff -s s21_grep.txt grep.txt
