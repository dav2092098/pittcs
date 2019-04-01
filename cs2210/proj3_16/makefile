seman:    seman.c y.tab.c lex.yy.c proj2.c proj3.c
	gcc -g -o seman seman.c y.tab.c proj2.c proj3.c -lfl

parser:   parser.c y.tab.c lex.yy.c proj2.c
	gcc -D parser -g -o parser parser.c y.tab.c proj2.c -lfl

lexer:    lex.yy.c lexer_main.c table.c
	gcc -D lex -o lexer lex.yy.c lexer_main.c -ll

y.tab.c:  grammar.y
	yacc -v grammar.y

lex.yy.c: lex.l table.c 
	flex lex.l table.c
