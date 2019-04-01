#include "proj2.h"
#include "proj3.h"
#include <stdio.h> 
#include <stdlib.h> 

int st[ST_SIZE];

attr_type attrarray[ATTR_SIZE];

int stack_top = 0;	     /* stack top counter */
int st_top = 0;		     /* symbol table top counter */
int nesting = 0;	     /* nesting level counter */
int attr_top = 0;	     /* attribute array counter */

extern int yyline;
extern char string_table[];      

int mainDef = 0;

void
STInit()
{
	int nStrInd, nSymInd;  

	nStrInd = search("system"); 
	if ( nStrInd != -1 )         
	{
		nSymInd = InsertEntry(nStrInd);
		SetAttr(nSymInd, PREDE_ATTR, true);
		SetAttr(nSymInd, KIND_ATTR, CLASS);
	}

	nStrInd = search("readln");
	if ( nStrInd != -1 )
	{
		nSymInd = InsertEntry(nStrInd);
		SetAttr(nSymInd, NEST_ATTR, nesting+1);
		SetAttr(nSymInd, PREDE_ATTR, true);
		SetAttr(nSymInd, KIND_ATTR, PROCE);
	}

	nStrInd = search("println");
	if ( nStrInd != -1 )
	{
		nSymInd = InsertEntry(nStrInd);
		SetAttr(nSymInd, NEST_ATTR, nesting+1);
		SetAttr(nSymInd, PREDE_ATTR, true);
		SetAttr(nSymInd, KIND_ATTR, PROCE);
		SetAttr(nSymInd, ARGNUM_ATTR, 1);
	}
}


void error_msg(type, action, id, seq)
int type, action, id, seq;
{
	printf("Semantic Error--line: %d, ", yyline);
	switch (type)
	{
		case STACK_OVERFLOW:
			printf("stack overflow.\n");
			break;
		case REDECLARATION:
			printf("symbol %s: redeclared.\n", getname(id));
			break;
		case ST_OVERFLOW:
			printf("symbol table overflow.\n");
			break;
		case UNDECLARATION:
			printf("symbol %s: undeclared.\n", getname(id));
			break;
		case ATTR_OVERFLOW:
			printf("attribute array overflowed.\n");
			break;
		case BOUND:
			printf("symbol %s: not declared as a constant, can't be used as subrange bound.\n", getname(id));
			break;
		case ARGUMENTS_NUM1:
			printf("routine %s: argument number in definition is different with the previous forward declaration. \n", getname(id));
			break;
		case ARGUMENTS_NUM2:
			printf("routine %s: argument number is different with the previous declaration. \n", getname(id));
			break;
		case FORW_REDECLARE:
			printf("routine %s: forward redeclaration.\n", getname(id));
			break; 
		case PROCE_MISMATCH: 
			printf("symbol %s: can't act as a procedure call.\n", getname(id)); 
			break;
		case FUNC_MISMATCH:
			printf("symbol %s: can't act as a function call.\n", getname(id));
			break;
		case VAR_VAL:
			printf("routine %s: reference/value type of the ", getname(id));
			printf("%s parameter different with previous forward declaration.\n", seq_str(seq));
			break;
		case CONSTANT_VAR:
			printf("routine %s: the ", getname(id));
			printf("%s parameter is a reference argument, can't be a constant.\n", seq_str(seq));
			break;
		case EXPR_VAR:
			printf("routine %s: reference argument of the ", getname(id));
			printf("%s parameter can't be a expression. \n", seq_str(seq));	
			break;
		case CONSTANT_ASSIGN:
			printf("symbol %s: declared to be a constant, can't be assigned a new value.\n", getname(id));
			break;
		case ARR_TYPE_MIS:
			if (seq == 0) 
			{
				printf("symbol %s: isn't defined as an array.\n", getname(id));
			}
			else
			{
				printf("symbol %s: the ", getname(id));
				printf("%s index isn't defined as an array.\n", seq_str(seq));
			}
			break;
		case ARR_DIME_MIS:
			printf("symbol %s: inappropriate usage of arry element.\n", getname(id));
			break;
		case REC_TYPE_MIS:
			printf("symbol %s: illegal usage of a field name. \n", getname(id));
			break;
		case INDX_MIS:
			printf("symbol %s: has incorrect number of dimensions.\n", getname(id));			
			break;
		case FIELD_MIS:
			printf("symbol %s: is an undeclared field name.\n", getname(id));
			break;
		case VARIABLE_MIS:
			printf("symbol %s: can't be used as a variable.\n", getname(id));
			break;
		case NOT_TYPE:
			printf("symbol %s: is not declared as a type.\n", getname(id));
			break;
		case TYPE_MIS:
			printf("symbol %s: incorrect type usage.\n", getname(id));
			break;
		case MULTI_MAIN:
			printf("main() method already declared.\n");
			break;
		case STRING_MIS:
			printf("symbol %s: is String Contstant outside of an output function.\n", getstring(id));
			break;
		default:
			printf("error type: %d.\n", type);
	}
	if (action == ABORT) 
	{
		exit(0);
	}
}

int
InsertEntry(id)
int id;
{
	if (!strncmp(getname(id), "main", 4)) {
		if (mainDef == 1) {
			error_msg(MULTI_MAIN, CONTINUE, 0, 0);
			return -1;
		}
		mainDef = 1;
	}
	
	if (LookUpHere(id))
	{
		error_msg(REDECLARATION, CONTINUE, id, 0);
		return (0);
	}

	if (st_top >= ST_SIZE-1)
		error_msg(ST_OVERFLOW, ABORT, 0 ,0);

	st_top++;
	st[st_top] = 0;
	SetAttr(st_top, NAME_ATTR, id);
	SetAttr(st_top, NEST_ATTR, nesting);
	Push(false, id, st_top, false);
	return (st_top);
}

int
LookUp(id)
int id;
{
	int i;

	for (i = stack_top; i > 0; i--)
	{
		if (!stack[i].marker && stack[i].name == id)
		{
			stack[i].used = true;
			return (stack[i].st_ptr);
		}
	}
	
	error_msg(UNDECLARATION, CONTINUE, id, 0);
	Push(false, id, 0, true);
	return 0;
}

int findClass(id)
int id;
{
	int toReturn = -1;
		if (IsAttr(id, KIND_ATTR)) {
		if ((int)GetAttr(id, KIND_ATTR) == CLASS) {
			toReturn = id;
		} else {
			if (IsAttr(id, TYPE_ATTR)) {
				tree type = (tree)GetAttr(id, TYPE_ATTR);				
				type = LeftChild(type);
				if (NodeKind(type) == STNode) {
					int index = IntVal(type);
					if ((int)GetAttr(index, KIND_ATTR) == CLASS) {
						toReturn = index;
					}
				}
			}
		}
	}
	return toReturn;
}

int
LookUpHere(id)
int id;
{
	int i;

	for (i = stack_top; !stack[i].marker; i--)
	{
		if (stack[i].name == id && !stack[i].dummy)
		{
			return (stack[i].st_ptr);
		}
	}
	return (0);
}

int LookUpField(class, field)
int class;
int field;
{
	int i;
	for(i += class + 1; i <= st_top; i++) {
		
		if ((int)GetAttr(i, NAME_ATTR) == field) {
			if ((int)GetAttr(i, NEST_ATTR) == 1) { 				
				return (i);
			}	
		}
		if ((int)GetAttr(i, KIND_ATTR) == CLASS) {
			break;
		}
	}
	error_msg(FIELD_MIS, CONTINUE, field, 0);
	Push(false, field, 0, true);
	return 0;
}

void
OpenBlock()
{
	nesting++;
	Push(true, 0, 0, false);		 
}

void
CloseBlock()
{
	int i;

	for (i = stack_top; !stack[i].marker; i--)
	{
		if (!stack[i].used && !stack[i].dummy)
		{
			
		}
	}

	nesting--;
	stack_top = i - 1;				 
}

int
IsAttr(st_ptr, attr_num)
int st_ptr, attr_num;
{
	int i;

	i = st[st_ptr];
	while (i)
	{
		if (attrarray[i].attr_num == attr_num)
			return (i);
		if (attrarray[i].attr_num > attr_num)
			break;
		i = attrarray[i].next_attr;
	}
	return (0);
}

uintptr_t
GetAttr(st_ptr, attr_num)
int st_ptr, attr_num;
{
	int i;

	i = IsAttr(st_ptr, attr_num);
	if (!i)
	{
		printf("DEBUG--The wanted attribute number %d does not exist\n", attr_num);
		return (0);
	}

	return (attrarray[i].attr_val);
}

void
SetAttr(st_ptr, attr_num, attr_val)
int st_ptr, attr_num;
uintptr_t attr_val;
{
	int *p, next;
	int i;
	if (i = IsAttr(st_ptr, attr_num))
	{
		attrarray[i].attr_val = attr_val;
		return;
	}

	p = &st[st_ptr];
	next = st[st_ptr];

	while (next)
	{
		if (attrarray[next].attr_num < attr_num)
		{
			p = &(attrarray[next].next_attr);
			next = attrarray[next].next_attr;
		}
		else
		{
			break;
		}
	}

	if (attr_top >= ATTR_SIZE-1)
	{
		error_msg(ATTR_OVERFLOW, ABORT,0, 0);
	}
	
	attr_top++;
	attrarray[attr_top].attr_num = attr_num;
	attrarray[attr_top].attr_val = attr_val;
	attrarray[attr_top].next_attr = next;
	*p = attr_top;
}

extern FILE *table;

char *kind_name[] =
{"constant", "variable","funcforw", "function", "ref_arg", "val_arg", "field",
	"typedef", "procforw",  "procedure", "class", "array"
};

void
STPrint()
{
	FILE *table;
	int i, attr_num, attr_ptr, type_attr;
	uintptr_t attr_val;
	int treeval = 0;
	tree ptrTree;

	table = stdout;
	fprintf(table,
		"********************************Symbol Table************************************\n\n");
	fprintf(table,
		"          Name Nest-Level  Tree-Node Predefined        Kind       Type      Value  Offset Dimension   Argnum\n\n");

	for (i = 1; i <= st_top; i++)
	{
		treeval = 0;
		fprintf(table, "%3d", i);
		for (attr_num = NAME_ATTR; attr_num <= ARGNUM_ATTR; attr_num++)
		{
			if (attr_ptr = IsAttr(i, attr_num))
			{
				attr_val = attrarray[attr_ptr].attr_val;
				switch (attr_num)
				{
					case NAME_ATTR:
						fprintf(table, "%11s", getname(attr_val));
						break;
					case OFFSET_ATTR:
					case NEST_ATTR:
					case TREE_ATTR:
						fprintf(table, "%11d", (int)attr_val);
						break;
					case TYPE_ATTR:
						treeval = attr_val;
						fprintf(table, "%11d", (int)attr_val);
						break;
					case PREDE_ATTR:
						if (attr_val == true)
							fprintf(table, "%11s", "yes");
						else 
							fprintf(table, "%11s", "no");
						break;
					case KIND_ATTR:
						fprintf(table, "%11s", kind_name[attr_val - 1]);
						break;
					case VALUE_ATTR:
						if (GetAttr(i, KIND_ATTR) == CONST)
						{
							ptrTree = (tree)attr_val;
							switch (NodeKind(ptrTree))
							{
								case NUMNode:
									fprintf(table, "%11d", IntVal(ptrTree));
									break;
								case CHARNode:
									if (isprint (IntVal(ptrTree)))
										fprintf(table, "%11c", IntVal(ptrTree));
									break;
								case STRINGNode:
									fprintf(table, "%11s", getstring(IntVal(ptrTree)));
									break;
							}
						}
						break;
					case DIMEN_ATTR:
						fprintf(table, "%11d", (int)attr_val);
						break;
					case ARGNUM_ATTR:
						fprintf(table, "%11d", (int)attr_val);
						break;
				}
			}
			else {
				fprintf(table, "%11s", " ");
			}			
		}
		fprintf(table, "\n");
	}
}


void
Push(marker, name, st_ptr, dummy)
int marker,name,st_ptr,dummy;
{
	if (stack_top >= STACK_SIZE-1)
		error_msg(STACK_OVERFLOW, ABORT,0, 0);

	stack_top++;

	stack[stack_top].marker = (bool) marker;
	stack[stack_top].name = name;
	stack[stack_top].st_ptr = st_ptr;
	stack[stack_top].dummy = (bool) dummy;
	stack[stack_top].used = false;
}

char *seq_str(seq)
int seq;
{
	static char s[10];
	switch (seq)
	{
		case 0:
			return("0th");
		case 1:
			return("1st");
		case 2:
			return("2nd");
		case 3:
			return("3rd");
		default:
			sprintf(s, "%dth", seq);
			return(s);
	}
}
