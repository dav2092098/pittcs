LEX = lex

CC = gcc

all: lex.yy.c lexer_main.c
	$(CC) lexer_main.c -o lexer -ll

lex.yy.c: lexer.l
	$(LEX) lexer.l
