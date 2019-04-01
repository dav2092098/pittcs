#include <stdio.h>
#include "proj2.h"
#include "table.h"
#include "token.h"

extern int yylex();
extern int yyline, yycolumn;
extern YYSTYPE yylval;

/* Array of Token Names for final output */
const char * tokens[] = {
	"ANDnum",
	"ASSGNnum",
	"DECLARATIONSnum",
	"DOTnum",
	"ENDDECLARATIONSnum",
	"EQUALnum",
	"GTnum",
	"IDnum",
	"INTnum",
	"LBRACnum",
	"LPARENnum",
	"METHODnum",
	"NEnum",
	"ORnum",
	"PROGRAMnum",
	"RBRACnum",
	"RPARENnum",
	"SEMInum",
	"VALnum",
	"WHILEnum",
	"CLASSnum",
	"COMMAnum",
	"DIVIDEnum",
	"ELSEnum",
	"EQnum",
	"GEnum",
	"ICONSTnum",
	"IFnum",
	"LBRACEnum",
	"LEnum",
	"LTnum",
	"MINUSnum",
	"NOTnum",
	"PLUSnum",
	"RBRACEnum",
	"RETURNnum",
	"SCONSTnum",
	"TIMESnum",
	"VOIDnum"
};

int main() {
	int lexReturn;
	printf("Line\tColumn\tToken\t\tIndex_in_String_Table\n");
	do {
		lexReturn = yylex();
		switch(lexReturn) {
			case EOFnum:
				printf("\t\t%s\t\n", "EOFnum");
				break;
			case IDnum:
				printf("%d\t%d\t%s\t\t%d\n", yyline, yycolumn, tokens[lexReturn - 257], yylval.intg);
				break;
			case SCONSTnum:
			  printf("%d\t%d\t%s\t%d\n", yyline, yycolumn, tokens[lexReturn - 257], yylval.intg);
			  break;
			case ICONSTnum:
				printf("%d\t%d\t%s\t\n", yyline, yycolumn, tokens[lexReturn - 257]);

				break;	
			default:
				printf("%d\t%d\t%s\t\n", yyline, yycolumn, tokens[lexReturn - 257]);
		}
	} while (lexReturn != 0);
	print_string_table();
	printf("End of File\n");
}
