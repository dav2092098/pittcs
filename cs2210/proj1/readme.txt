CS2210 Proj 1

Lexical analyzer

Lexical rules are in lexer.l
The project can be compiled as follows:
$	make
This will run a make file that runs the commands
$	lex lexer.l (makes lex generates lex.yy.c)
$	gcc lex.yy.c -o lexer -ll
The lexer can then be run on files with the command
$	./lexer < file.txt

The total length of all string constants and identifier
names are limited to 500. This is set with #define LIMIT1 500 as described in the notes.

The columns tell location of the end of token as in the project example.

Tabs are assumed to be 4 spaces and 4 was used for column count purposes.
