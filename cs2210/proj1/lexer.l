%{
#include <stdlib.h>
#include <string.h>
#include "token.h"

#define LIMIT1 500
#define LIMIT2 4096

extern int yycolumn, yylength, yyline, yylval;

int tbl_index, pos();

char* tolowercase(char c[]);

void output_error(char str[]);
void symbolTablePrint();
void string_table(char str[]);

int search(char str[]);
int insert(char str[]);

char string_buf[LIMIT1];
char string_buf2[LIMIT2];
char *string_buf_ptr;
char *string_but_ptr2;

int str_error = 0;
%}

%x comment
%x str

/* regex tokenizing */
letter						[A-Za-z]
digit						[0-9]
delim						[ \t]
ws						{delim}+
newline						[\n(\r\n)]
declarations					((D|d)(E|e)(C|c)(L|l)(A|a)(R|r)(A|a)(T|t)(I|i)(O|o)(N|n)(S|s))
enddeclarations					((E|e)(N|n)(D|d)(D|d)(E|e)(C|c)(L|l)(A|a)(R|r)(A|a)(T|t)(I|i)(O|o)(N|n)(S|s))
int						((I|i)(N|n)(T|t))
method						((M|m)(E|e)(T|t)(H|h)(O|o)(D|d))
program						((P|p)(R|r)(O|o)(G|g)(R|r)(A|a)(M|m))
val						((V|v)(A|a)(L|l))
while_def					((W|w)(H|h)(I|i)(L|l)(E|e))
class						((C|c)(L|l)(A|a)(S|s)(S|s))
else_def					((E|e)(L|l)(S|s)(E|e))
if_def						((I|i)(F|f))
return_def					((R|r)(E|e)(T|t)(U|u)(R|r)(N|n))
void						((V|v)(O|o)(I|i)(D|d))
ICONSTnum					([1-9]{digit}*|0)
IDnum						{letter}({letter}|{digit})*
BADIDnum					{digit}({letter}|{digit})*

%%

"/*"						{BEGIN(comment);}
<comment>{
	[^*\n]*					/* Discard any non '*' */
	"*"+[^*/\n]				/* Discard any '*' not followed by '/' */
	\n					{yyline++; yycolumn = 0;}
	<<EOF>>					{output_error("Unterminated Comment"); 
						 BEGIN(INITIAL);}
	"*"+"/"					BEGIN(INITIAL);
}
"&&"						{pos(); return(ANDnum);}
":="						{pos(); return(ASSGNnum);}
{declarations} 					{pos(); return(DECLARATIONSnum);}
"." 						{pos(); return(DOTnum);}
{enddeclarations}				{pos(); return(ENDDECLARATIONSnum);}
"="						{pos(); return(EQUALnum);}
">"						{pos(); return(GTnum);}
{int} 						{pos(); return(INTnum);}
"[" 						{pos(); return(LBRACnum);}
"(" 						{pos(); return(LPARENnum);}
{method} 					{pos(); return(METHODnum);}
"!="						{pos(); return(NEnum);}
"||"						{pos(); return(ORnum);}
{program}					{pos(); return(PROGRAMnum);}
"]"						{pos(); return(RBRACnum);}
")"						{pos(); return(RPARENnum);}
";"						{pos(); return(SEMInum);}
{val}						{pos(); return(VALnum);}
{while_def}					{pos(); return(WHILEnum);}
{class}						{pos(); return(CLASSnum);}
","						{pos(); return(COMMAnum);}
"/"						{pos();	return(DIVIDEnum);}
{else_def}					{pos(); return(ELSEnum);}
"=="						{pos(); return(EQnum);}
">="						{pos(); return(GEnum);}
{if_def}					{pos(); return(IFnum);}
"{"						{pos(); return(LBRACEnum);}
"<="						{pos(); return(LEnum);}
"<"						{pos(); return(LTnum);}
"-"						{pos(); return(MINUSnum);}
"!"						{pos(); return(NOTnum);}
"+" 						{pos(); return(PLUSnum);}
"}"						{pos(); return(RBRACEnum);}
{return_def}					{pos(); return(RETURNnum);}
"*"						{pos(); return(TIMESnum);}
{void}						{pos(); return(VOIDnum);}

{ICONSTnum}					{pos();
						 yylval = atoi(yytext); 
						 return(ICONSTnum);}

\'						{string_buf_ptr = string_buf;
						 pos();
						 *string_buf_ptr++ = '\'';						
						 BEGIN(str);}
<str>{
	\'					{ /* Closing Quote, all done  */
      				                      *string_buf_ptr++ = '\'';
							pos();
							BEGIN(INITIAL);
							*string_buf_ptr = '\0';
							string_table(string_buf);
							return(SCONSTnum);
						}
	\n					pos();
	\\n					pos(); *string_buf_ptr++ = '\n';
	\\t					pos(); *string_buf_ptr++ = '\t';
	\\\'					pos(); *string_buf_ptr++ = '\'';
	<<EOF>>					{output_error("EOF Unterminated String"); BEGIN(INITIAL);}
	.					{pos();
						 *string_buf_ptr++ = *yytext;
						}
}

{IDnum}						{pos();
						 string_table(yytext);
						 return(IDnum);}

{ws}						{pos();}
{newline} 					{pos();}
{BADIDnum}					{pos();
						 output_error("Bad Identifier");}
.						{pos();
   						 output_error("Bad Lexeme");}

%%

char symbolTable[LIMIT1 + 1];
//char symbolTable[LIMIT2 + 1];

int yyline = 1;
int yycolumn = 1;
int yylval = 0;
int tbl_index = 0;

/* Token names list*/
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

/* pos() func to track the line and column num */
int pos() {
	/* Reset line num and column num when '\n' is seen */
	if (yytext[0] == '\n') {
		yyline++;
		yycolumn = 0;
	} 
	else {
    		int i;
		for (i = 0; yytext[i] != '\0'; i++) {
			/* if '\t' is seen, move the column right 4 spaces (and account for extra space at begining) */
    			if (yytext[i] == '\t') {
    				yycolumn += 4 - (yycolumn % 4);
    			}
			/* move column one space */
    			else {
    				yycolumn++;
    			}
    		}
  	}
}

/* Print symbol table*/
void symbolTablePrint() {
	printf("Symbol Table: ");
	int i;
	for (i = 0; i < tbl_index; i++) {
		while (symbolTable[i] != '\0') {
			printf("%c", symbolTable[i]);
			i++;
		}
		printf("%c", ' ');
	}
	printf("\n");
}

/* func to handle addition to the symbolTable */
void string_table(char c[]) {
	/* Search for the string in the table */
	int search_index = search(c);
	/* if string is not found, insert into table and return index where inserted */
	if (search_index == -1) {
		c = tolowercase(c); /*convert*/
		yylval = insert(c);
	/* if found return index it was found at */
	} 
	else {
		yylval = search_index;
	}
}

char* tolowercase(char c[]) {
/* transform an identifier to lower case representation */
  	int i;
	for(i = 0; i < yyleng; i++ ) {
     		if ( 'A' <= c[i] && c[i] <= 'Z' ) {
        		c[i] = c[i] - 'A' + 'a';
		}
  	}
  	return c;
}

/* insert into symbolTable */
int insert(char c[]) {
	/* Check if there is room for the string */
	if (strlen(c) + tbl_index >= LIMIT1) {
		printf("Lexeme too long.\n");
		return -1;
	}
	/* Copy the string into the table */
	strcpy(&(symbolTable[tbl_index]), c);
	/* Set new end index and return there the string was inserted */
	int temp = tbl_index;
	tbl_index += strlen(c) + 1;
	return temp;
}


int search(char c[]) {
	int i = 0;
	char word[LIMIT1];
	symbolTable[LIMIT1] = '\0';
	
	while (i < LIMIT1) {
		strcpy(&word[0], &(symbolTable[i]));
		if (!strcasecmp(word, c)) {
			return i;
		} 
		else {
			i = i + strlen(word);
		}
		i++;
	}
	return -1;
}

/* Error output */
void output_error(char c[]) {
	printf("ERROR: %s at Line: %d, Column: %d\n", c, yyline, yycolumn);
}
