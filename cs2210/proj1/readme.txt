CS 1622 Compilers Project 1
Brian Lester bdl20@pitt.edu 2-9-16

This is my project 1 for CS 1622 lexical analysis
Lexical rules are in lexer.l
The project can be compiled as follows:
	make
This will run a make file that runs the commands
	lex lexer.l (makes lex generates lex.yy.c)
	gcc lex.yy.c -o lexer -ll
The lexer can then be run on files with the command
	./lexer < file.txt

The total length of all string constants and identifier
names are limited to 500. This is set with 
#define LIMIT1 500 as described in the notes.

This implementation supports multiline comments and multiline strings. 
The professor told me this was fine if I mentioned it in the readme

The columns tell location of the end of token as in the project example.

Tabs are assumed to be 4 spaces and 4 was used for column count purposes.
