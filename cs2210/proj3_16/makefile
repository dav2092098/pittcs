# semantics.c depends on y.tab.c which depends on grammar.y => grammar.y will be compiled with yacc
# semantics.c also depends on lex.yy.c which depends on lex.l and strtable.c => lex.l will be compiled with flex and strtable.c
# semantics.c also depends on proj2.c and proj3.c

semantics:    semantics.c y.tab.c lex.yy.c proj2.c proj3.c
	gcc -g -o semantics semantics.c y.tab.c proj2.c proj3.c -lfl

#parser:   parser.c y.tab.c lex.yy.c proj2.c
#	gcc -D parser -g -o parser parser.c y.tab.c proj2.c -lfl

#lexer:     lex.yy.c lexer_main.c table.c
#	gcc -D lex -o lexer lex.yy.c lexer_main.c -ll

y.tab.c:  grammar.y
	yacc -v grammar.y

lex.yy.c: lex.l strtable.c 
	flex lex.l strtable.c

clean: 	
	rm -v lex.yy.c y.tab.c y.output semantics
