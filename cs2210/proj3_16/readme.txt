Ayodele, David
CS 2210 Project 3
04/01/2019

This implements project 3 - semantic analysis.

This may be compiled as follows:
1)$	make
Executes a makefile that performs the following:
	flex lex.l (generates lex.yy.c)
	yacc -v grammar.y (generates y.tab.c)
	gcc -g -o semantics semantics.c y.tab.c proj2.c proj3.c -lfl

2) $ ./semantics < file
Runs the semantic analyzer on a file

This was compiled and tested on oxygen.cs.pitt.edu and germanium.cs.pitt.edu 

This project uses files from projects 1 and 2. Some discrepancies in the prior projects therefore carry over into this one. For example, the ignoring of letter case is carried over as well as the shift reduce conflicts from project 2.
