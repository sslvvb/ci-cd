#!/bin/sh

sshpass -p password123 scp src/artifacts/s21_cat src/artifacts/s21_grep test2@192.168.64.19:/usr/local/bin
