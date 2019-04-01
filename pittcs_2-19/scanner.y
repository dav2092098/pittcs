%{
void yyerror (char *s);
#include<stdio.h>  /* C declarations used in actons */
#include<stdlib.h>
int symbols[52];
int symbolVal(char symbol);
voide updateSymbolVal(char symbol, int val);
%}

%union {int num; char id;} /* Yacc definitions */
%start line
%token print
%token exit_command
%token <num> number
%token <id> identifier
%token <num> line exp term
%type <id> assignment

%%

/* Descriptions of expected inputs   corresponding to actions (in C) */

line	: assignment ';'	{;}
	| exit_command ';'	{exit(EXIT_SUCCESS);}
	| print exp ';'		{printf("Printing %d\n", $2);}
	| line assignment ';'	{;}
	| line exit_command ';'	{exit(EXIT_SUCCESS);}
	;

assignment : identifier '=' exp { updateSymbolVal($1, $3); };
exp	: term		{$$ = $1;}
	| exp '+' term	{$$ = $1 + $3;}
 	| exp '-' term 	{$$ = $1 - $3;}
	;
term	: number	{$$ = $1;}
	| identifier	{$$ = symbolVal($1);}

%%  	/* C code */

int computeSymbolIndex(char token) {
	int index = -1;
	if(islower(token)) {
		index = token - 'a' + 26; 
	} else if (isupper(token)) {
		index = token - 'A';
	}
	return index;
}

/* returns the value of a given symbol */
int symbolVal (char symbol) {
	int box = computeSymbolIndex(symbol);
	return symbols[box];
}

/* updates the value of a given symbol */
void updateSymbolVal (char symbol, int val) {
	int box = computeSymbolIndex(symbol);
	symbols[box] = val;
}

int main (void) {
	/* init symbol table */
	int i;
	for (i = 0; i < 52; i++) {
		symbols[i] = 0;
	}
	return yyparse();
}

void yyerror (char *s) {
	fprintf (stderr, "%s\n", s);
}


