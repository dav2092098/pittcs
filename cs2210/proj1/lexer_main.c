#include <stdio.h>
#include "lex.yy.c"

extern int yylex(); /*returns results of tokenization, lexical analysis*/
//extern int yylineno;
//extern char* yytext;
extern void symbolTablePrint();

main() {
	int ntoken, vtoken;
	printf("Line\tColumn\tToken\t\tIndex in String table\n");
	//printf("----\t------\t-----\t\t---------------------\n");
	do {
		ntoken = yylex();
		switch(ntoken) {
			case EOFnum:
				printf("\t\t%s\t\n", "EOFnum");
				break;
			case IDnum:
				printf("%d\t%d\t%s\t\t%d\n", yyline, yycolumn, tokens[ntoken - 257], yylval);
				break;
			case SCONSTnum:
			  printf("%d\t%d\t%s\t%d\n", yyline, yycolumn, tokens[ntoken - 257], yylval);
			  break;
			case ICONSTnum:
				printf("%d\t%d\t%s\t\n", yyline, yycolumn, tokens[ntoken - 257]);
				break;	
			default:
				printf("%d\t%d\t%s\t\n", yyline, yycolumn, tokens[ntoken - 257]);
		}
	} while (ntoken != 0);
	symbolTablePrint();
	printf("End\n");
}
