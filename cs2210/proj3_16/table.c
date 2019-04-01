#include <stdio.h>
#include <string.h>

#include "table.h"
#include "proj2.h"

extern char string_table[];
extern int st_index;
extern int yyleng;
extern YYSTYPE yylval; 

/*==== Prints symbol table ====*/
void print_string_table() {
	int i;
	printf("String Table: ");
	for (i = 0; i < st_index; i++) {
		while (string_table[i] != '\0') {
			printf("%c", string_table[i]);
			i++;
		}
		printf("%c", ' ');
	}
	printf("\n");
}
/*=========*/

char * tolowercase(char a[]) {
	int i;
	for( i=0; i<yyleng; i++ ) {
		if ( 'A'<=a[i] && a[i]<='Z' )
		a[i] = a[i] - 'A' + 'a';
	}
	return a;
}

void add_to_string_table(char a[]) {
	int search_index = search(a);
	if (search_index == -1) {
		a = tolowercase(a);
		yylval.intg = insert(a);
	} else {
		yylval.intg = search_index;
	}
}

int insert(char a[]) {
	if (strlen(a) + st_index >= LIMIT1) {
		printf("Lexeme too long.\n");
		return -1;
	}
	strcpy(&(string_table[st_index]), a);
	int temp = st_index;
	st_index += strlen(a) + 1;
	return temp;
}

int search(char a[]) {
	int i = 0;
	char word[LIMIT1];
	string_table[LIMIT1] = '\0';
	while (i < LIMIT1) {
		strcpy(&word[0], &(string_table[i]));
		if (!strcasecmp(word, a)) {
			return i;
		}
		else {
			i = i + strlen(word);
		}
		i++;
	}
	return -1;
}
