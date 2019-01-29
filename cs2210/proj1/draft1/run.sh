#! /bin/sh

lex myscanner.l
gcc -o myscanner lex.yy.c myscanner.c  
