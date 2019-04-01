#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#include <stdlib.h>
#include <string.h>

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20070509

#define YYEMPTY (-1)
#define yyclearin    (yychar = YYEMPTY)
#define yyerrok      (yyerrflag = 0)
#define YYRECOVERING (yyerrflag != 0)

extern int yyparse(void);

static int yygrowstack(void);
#define YYPREFIX "yy"
#line 2 "grammar.y"
#include "proj2.h"
#include <stdio.h>

  tree root;
  tree type_method, argtype, bractemp, type_tree; /* globals used to store treenode pointers */
  int type_record;
  int error = 0;

#line 32 "y.tab.c"
#define PROGRAMnum 257
#define IDnum 258
#define SEMInum 259
#define CLASSnum 260
#define DECLARATIONSnum 261
#define ENDDECLARATIONSnum 262
#define COMMAnum 263
#define EQUALnum 264
#define LBRACEnum 265
#define RBRACEnum 266
#define LBRACnum 267
#define RBRACnum 268
#define LPARENnum 269
#define RPARENnum 270
#define VOIDnum 271
#define INTnum 272
#define METHODnum 273
#define VALnum 274
#define DOTnum 275
#define ASSGNnum 276
#define RETURNnum 277
#define IFnum 278
#define ELSEnum 279
#define WHILEnum 280
#define LTnum 281
#define LEnum 282
#define EQnum 283
#define NEnum 284
#define GEnum 285
#define GTnum 286
#define PLUSnum 287
#define MINUSnum 288
#define ORnum 289
#define TIMESnum 290
#define DIVIDEnum 291
#define ANDnum 292
#define NOTnum 293
#define ICONSTnum 294
#define SCONSTnum 295
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    1,    1,    2,    3,    4,    4,    5,    5,    6,
   50,    6,    7,    7,    7,    7,    8,    8,    8,    9,
    9,   10,   10,   51,   11,   52,   11,   12,   12,   13,
   13,   14,   15,   15,   16,   16,   16,   16,   16,   16,
   17,   17,   18,   18,   18,   19,   20,   20,   21,   21,
   22,   22,   23,   23,   24,   24,   24,   25,   26,   26,
   27,   28,   28,   29,   30,   31,   32,   32,   32,   33,
   33,   34,   34,   34,   35,   36,   36,   36,   36,   36,
   36,   36,   37,   37,   37,   37,   37,   38,   38,   39,
   39,   39,   40,   40,   41,   41,   41,   42,   43,   43,
   44,   44,   44,   45,   46,   46,   46,   47,   48,   49,
   49,
};
short yylen[] = {                                         2,
    4,    1,    2,    3,    4,    1,    2,    0,    1,    7,
    0,    8,    2,    2,    4,    4,    0,    2,    3,    0,
    1,    1,    3,    0,    4,    0,    3,    1,    3,    1,
    2,    3,    1,    3,    0,    1,    1,    1,    1,    1,
    0,    3,    0,    1,    2,    3,    1,    3,    1,    3,
    1,    2,    2,    3,    1,    1,    1,    3,    1,    3,
    2,    1,    2,    3,    3,    4,    0,    1,    3,    1,
    2,    3,    5,    5,    3,    1,    3,    3,    3,    3,
    3,    3,    1,    1,    1,    3,    2,    1,    1,    2,
    3,    3,    0,    2,    2,    2,    2,    2,    0,    2,
    2,    2,    2,    2,    0,    2,    2,    2,    3,    1,
    3,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    2,    0,    3,    0,
    4,    0,    0,    0,    0,    0,    0,   44,    0,    0,
    6,    9,    0,    0,    0,    0,    0,   47,    0,   42,
   45,   11,    0,    5,    7,   18,    0,    0,    0,    0,
    0,   46,    0,    0,    0,    0,   19,   15,   16,   53,
    0,   48,    0,    0,    0,    0,    0,    0,    0,   88,
   89,   50,   56,   57,   85,   55,    0,   83,    0,    0,
    0,    0,    0,   54,    0,    0,  104,    0,    0,    0,
   59,    0,    0,    0,   62,    0,    0,   87,    0,    0,
    0,   98,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   90,    0,    0,    0,   26,   24,    0,   21,
    0,    0,    0,  108,  107,  106,    0,   58,   86,    0,
   63,   91,   92,  101,  102,  103,  100,   77,   78,   79,
   80,   81,   82,   95,   96,   97,   94,    0,    0,    0,
    0,    0,    0,    0,    0,  109,   60,   64,   66,    0,
    0,    0,   27,    0,    0,   10,   30,    0,   23,  111,
   69,   12,    0,   25,    0,    0,    0,    0,   33,   36,
   37,   38,   39,   40,    0,   31,   29,   71,    0,    0,
    0,   32,    0,    0,   75,   34,   65,    0,   73,   74,
};
short yydgoto[] = {                                       2,
    6,    7,   11,   20,   21,   22,   16,   24,  109,  110,
  111,  153,  156,  157,  168,  169,  158,   17,   18,   27,
   28,   29,   41,   62,   63,   80,   64,   84,   85,  170,
   65,  138,  172,  173,  174,  112,   67,   68,   69,  103,
  104,   70,   92,   93,   71,   77,   78,   79,  113,   45,
  142,  141,
};
short yysindex[] = {                                   -233,
 -179,    0, -160, -142, -139, -142,    0, -125,    0, -106,
    0, -206, -105, -115, -115,  -81, -245,    0, -215, -162,
    0,    0,  -90, -197, -173,  -67, -143,    0,  -62,    0,
    0,    0,  -49,    0,    0,    0,  -48, -206, -206,  -47,
  -57,    0,  -81, -253,  -39,  -46,    0,    0,    0,    0,
  -43,    0, -170, -240, -240,  -45, -244, -244, -244,    0,
    0,    0,    0,    0,    0,    0,  -77,    0,  -94,  -71,
  -42,  -41,  -89,    0, -240,  -34,    0, -170, -170, -189,
    0,  -40, -240,  -45,    0,  -71,  -71,    0, -244, -244,
 -244,    0,  -77, -240, -240, -240, -240, -240, -240, -244,
 -244, -244,    0,  -71, -240,  -89,    0,    0,  -38,    0,
  -33,  -32,  -35,    0,    0,    0, -240,    0,    0,  -31,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -36,  -28,  -30,
  -29,  -27,  -85,  -89, -240,    0,    0,    0,    0, -240,
  -85,  -25,    0,  -29, -182,    0,    0,  -26,    0,    0,
    0,    0,  -29,    0, -240, -240, -240, -238,    0,    0,
    0,    0,    0,    0, -161,    0,    0,    0,  -26,  -26,
 -182,    0, -240,  -37,    0,    0,    0, -165,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,  236,    0,    0,    0, -149,
    0,  -21,  -23, -243, -243,    0,    0,    0,    0,    0,
    0,    0,    0,  -14,  -12,  -60,    0,    0,  -52,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -58,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -201,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -122,    0,  -84, -112,
 -156,    0,  -22,    0,    0,    0,    0, -201, -201,    0,
    0,    0,    0,  -51,    0, -112, -112,    0,    0,    0,
    0,    0, -122,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -112,  -20,  -22,    0,    0,    0,    0,
  -18,  -17,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -15,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -20,
    0, -239,    0,    0, -121,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -117,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -121,    0,    0, -109,    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
    0,  241,    0,    0,    0,  229,  -16,  238,  148,  112,
    0,  -91,  106,  -87,    0,   77,  249,    0,  243,    0,
  218,    0,    0,    0,    0,    0,    0,    0,  178,    0,
 -151,  113,    0,   76,    0,  -44,  -53,    0,   99,  -78,
    0,  -56,  172,    0, -148,  -19,    0,    0,  121,    0,
    0,    0,
};
#define YYTABLESIZE 266
short yytable[] = {                                      66,
   86,   87,   33,  171,   53,   88,  175,  122,  123,   81,
   82,   54,   14,   53,   17,   55,   30,   53,   56,   28,
  181,   48,   49,    1,   55,  137,   15,  182,   55,  171,
   28,   17,  175,   57,   58,  124,  125,  126,  120,   59,
   60,   61,   14,  134,  135,  136,   57,   58,   59,   60,
   61,   14,   59,   60,   61,   32,   15,  105,  115,  116,
  139,  105,  164,  105,  105,   15,  105,  105,  105,   37,
  176,  177,  147,  117,  105,   53,  118,   38,    3,  105,
  105,  105,  105,  105,  105,  105,  105,  105,  105,  105,
  105,  184,  185,   37,  165,  166,   75,  167,    4,  155,
  189,   39,   84,   34,   76,  139,   84,  105,   84,   84,
   19,   84,  166,   84,  183,   42,   41,    5,    8,   43,
  178,  179,  180,   41,   84,   84,   84,   84,   84,   84,
   84,   84,   84,   84,   84,   84,   99,   35,  187,   10,
   99,   70,   99,   99,   35,   99,   93,   99,   70,   72,
   93,   23,   93,   93,   12,   93,   72,   93,   99,   99,
   99,   99,   99,   99,   99,   99,   99,   19,   93,   93,
   93,   93,   93,   93,   76,   12,   26,   36,   76,  155,
   76,   76,  107,   76,  108,   76,   94,   95,   96,   97,
   98,   99,  128,  129,  130,  131,  132,  133,   51,   40,
   52,   44,   51,   51,   52,   52,   49,   61,   46,   51,
   49,   61,   89,   90,   91,  100,  101,  102,   72,   47,
   50,   83,   73,  114,   74,  144,  105,  106,  152,  119,
  145,  143,  146,  149,  150,    1,  148,  163,  155,  151,
   43,  188,    8,   13,  154,   14,    9,   20,   35,   67,
  110,   22,   25,  140,   68,  159,  162,  186,   13,   31,
   52,  121,  161,  190,  127,  160,
};
short yycheck[] = {                                      44,
   57,   58,   19,  155,  258,   59,  155,   86,   87,   54,
   55,  265,  258,  258,  258,  269,  262,  258,  272,  259,
  259,   38,   39,  257,  269,  104,  272,  266,  269,  181,
  270,  275,  181,  287,  288,   89,   90,   91,   83,  293,
  294,  295,  258,  100,  101,  102,  287,  288,  293,  294,
  295,  258,  293,  294,  295,  271,  272,  259,   78,   79,
  105,  263,  154,  265,  266,  272,  268,  269,  270,  267,
  158,  163,  117,  263,  276,  258,  266,  275,  258,  281,
  282,  283,  284,  285,  286,  287,  288,  289,  290,  291,
  292,  179,  180,  267,  277,  278,  267,  280,  259,  265,
  188,  275,  259,  266,  275,  150,  263,  269,  265,  266,
  273,  268,  278,  270,  276,  259,  266,  260,  258,  263,
  165,  166,  167,  273,  281,  282,  283,  284,  285,  286,
  287,  288,  289,  290,  291,  292,  259,  259,  183,  265,
  263,  259,  265,  266,  266,  268,  259,  270,  266,  259,
  263,  267,  265,  266,  261,  268,  266,  270,  281,  282,
  283,  284,  285,  286,  287,  288,  289,  273,  281,  282,
  283,  284,  285,  286,  259,  261,  258,  268,  263,  265,
  265,  266,  272,  268,  274,  270,  281,  282,  283,  284,
  285,  286,   94,   95,   96,   97,   98,   99,  259,  267,
  259,  264,  263,  264,  263,  264,  259,  259,  258,  267,
  263,  263,  290,  291,  292,  287,  288,  289,  258,  268,
  268,  267,  269,  258,  268,  259,  269,  269,  258,  270,
  263,  270,  268,  270,  263,    0,  268,  263,  265,  270,
  262,  279,  266,  258,  272,  258,    6,  270,   20,  270,
  268,  270,   15,  106,  270,  144,  151,  181,   10,   17,
   43,   84,  150,  188,   93,  145,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 295
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"PROGRAMnum","IDnum","SEMInum",
"CLASSnum","DECLARATIONSnum","ENDDECLARATIONSnum","COMMAnum","EQUALnum",
"LBRACEnum","RBRACEnum","LBRACnum","RBRACnum","LPARENnum","RPARENnum","VOIDnum",
"INTnum","METHODnum","VALnum","DOTnum","ASSGNnum","RETURNnum","IFnum","ELSEnum",
"WHILEnum","LTnum","LEnum","EQnum","NEnum","GEnum","GTnum","PLUSnum","MINUSnum",
"ORnum","TIMESnum","DIVIDEnum","ANDnum","NOTnum","ICONSTnum","SCONSTnum",
};
char *yyrule[] = {
"$accept : Program",
"Program : PROGRAMnum IDnum SEMInum ClassDecl_rec",
"ClassDecl_rec : ClassDecl",
"ClassDecl_rec : ClassDecl_rec ClassDecl",
"ClassDecl : CLASSnum IDnum ClassBody",
"ClassBody : LBRACEnum Decls MethodDecl_List RBRACEnum",
"MethodDecl_List : MethodDecl_z1",
"MethodDecl_List : MethodDecl_List MethodDecl",
"MethodDecl_z1 :",
"MethodDecl_z1 : MethodDecl",
"MethodDecl : METHODnum Type IDnum LPARENnum Formal_Parameter_List RPARENnum Block",
"$$1 :",
"MethodDecl : METHODnum VOIDnum $$1 IDnum LPARENnum Formal_Parameter_List RPARENnum Block",
"Type : IDnum Type_rec",
"Type : INTnum Type_rec",
"Type : IDnum Type_rec DOTnum Type",
"Type : INTnum Type_rec DOTnum Type",
"Type_rec :",
"Type_rec : LBRACnum RBRACnum",
"Type_rec : Type_rec LBRACnum RBRACnum",
"Formal_Parameter_List :",
"Formal_Parameter_List : Formal_Parameter_List_rec",
"Formal_Parameter_List_rec : Formal_Parameter",
"Formal_Parameter_List_rec : Formal_Parameter SEMInum Formal_Parameter_List_rec",
"$$2 :",
"Formal_Parameter : VALnum $$2 INTnum Formal_Parameter_rec",
"$$3 :",
"Formal_Parameter : INTnum $$3 Formal_Parameter_rec",
"Formal_Parameter_rec : IDnum",
"Formal_Parameter_rec : IDnum COMMAnum Formal_Parameter_rec",
"Block : StatementList",
"Block : Decls StatementList",
"StatementList : LBRACEnum StatementList_rec RBRACEnum",
"StatementList_rec : Statement",
"StatementList_rec : StatementList_rec SEMInum Statement",
"Statement :",
"Statement : AssignmentStatement",
"Statement : MethodCallStatement",
"Statement : ReturnStatement",
"Statement : IfStatement",
"Statement : WhileStatement",
"Decls :",
"Decls : DECLARATIONSnum FieldDecl_List ENDDECLARATIONSnum",
"FieldDecl_List :",
"FieldDecl_List : FieldDecl",
"FieldDecl_List : FieldDecl_List FieldDecl",
"FieldDecl : Type FieldDecl_rec SEMInum",
"FieldDecl_rec : FieldDecl_Id",
"FieldDecl_rec : FieldDecl_rec COMMAnum FieldDecl_Id",
"FieldDecl_Id : VariableDeclId",
"FieldDecl_Id : VariableDeclId EQUALnum VariableInitializer",
"VariableDeclId : IDnum",
"VariableDeclId : IDnum BracketLoop",
"BracketLoop : LBRACnum RBRACnum",
"BracketLoop : BracketLoop LBRACnum RBRACnum",
"VariableInitializer : Expression",
"VariableInitializer : ArrayInitializer",
"VariableInitializer : ArrayCreationExpression",
"ArrayInitializer : LBRACEnum ArrayInitializer_rec RBRACEnum",
"ArrayInitializer_rec : Expression",
"ArrayInitializer_rec : ArrayInitializer_rec COMMAnum Expression",
"ArrayCreationExpression : INTnum ArrayCreationExpression_rec",
"ArrayCreationExpression_rec : ArrayExpression",
"ArrayCreationExpression_rec : ArrayCreationExpression_rec ArrayExpression",
"ArrayExpression : LBRACnum Expression RBRACnum",
"AssignmentStatement : Variable ASSGNnum Expression",
"MethodCallStatement : Variable LPARENnum ParameterList RPARENnum",
"ParameterList :",
"ParameterList : Expression",
"ParameterList : Expression COMMAnum ParameterList",
"ReturnStatement : RETURNnum",
"ReturnStatement : RETURNnum Expression",
"IfStatement : IFnum Expression StatementList",
"IfStatement : IFnum Expression StatementList ELSEnum StatementList",
"IfStatement : IFnum Expression StatementList ELSEnum IfStatement",
"WhileStatement : WHILEnum Expression StatementList",
"Expression : SimpleExpression",
"Expression : SimpleExpression LTnum SimpleExpression",
"Expression : SimpleExpression LEnum SimpleExpression",
"Expression : SimpleExpression EQnum SimpleExpression",
"Expression : SimpleExpression NEnum SimpleExpression",
"Expression : SimpleExpression GEnum SimpleExpression",
"Expression : SimpleExpression GTnum SimpleExpression",
"Factor : UnsignedConstant",
"Factor : Variable",
"Factor : MethodCallStatement",
"Factor : LPARENnum Expression RPARENnum",
"Factor : NOTnum Factor",
"UnsignedConstant : ICONSTnum",
"UnsignedConstant : SCONSTnum",
"SimpleExpression : Term SimpleExpression_Op_rec",
"SimpleExpression : PLUSnum Term SimpleExpression_Op_rec",
"SimpleExpression : MINUSnum Term SimpleExpression_Op_rec",
"SimpleExpression_Op_rec :",
"SimpleExpression_Op_rec : SimpleExpression_Op SimpleExpression_Op_rec",
"SimpleExpression_Op : PLUSnum Term",
"SimpleExpression_Op : MINUSnum Term",
"SimpleExpression_Op : ORnum Term",
"Term : Factor Term_Op_rec",
"Term_Op_rec :",
"Term_Op_rec : Term_Op Term_Op_rec",
"Term_Op : TIMESnum Factor",
"Term_Op : DIVIDEnum Factor",
"Term_Op : ANDnum Factor",
"Variable : IDnum Variable_rec",
"Variable_rec :",
"Variable_rec : Index Variable_rec",
"Variable_rec : Field Variable_rec",
"Field : DOTnum IDnum",
"Index : LBRACnum Index_rec RBRACnum",
"Index_rec : Expression",
"Index_rec : Expression COMMAnum Index_rec",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 500

int      yydebug;
int      yynerrs;
int      yyerrflag;
int      yychar;
short   *yyssp;
YYSTYPE *yyvsp;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* variables for the parser stack */
static short   *yyss;
static short   *yysslim;
static YYSTYPE *yyvs;
static int      yystacksize;
#line 605 "grammar.y"

int yycolumn, yyline;

FILE * treelst;

yyerror(char *str)
{
  printf("yyerror: %s at line %d\n", str, yyline);
  error = 1;
}

#include "lex.yy.c"
#line 420 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = yyssp - yyss;
    newss = (yyss != 0)
          ? (short *)realloc(yyss, newsize * sizeof(*newss))
          : (short *)malloc(newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    yyss  = newss;
    yyssp = newss + i;
    newvs = (yyvs != 0)
          ? (YYSTYPE *)realloc(yyvs, newsize * sizeof(*newvs))
          : (YYSTYPE *)malloc(newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

#ifdef lint
    goto yyerrlab;
#endif

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 36 "grammar.y"
{  
                       		yyval.tptr = MakeTree(ProgramOp, yyvsp[0].tptr, MakeLeaf(IDNode, yyvsp[-2].intg)); 
                      		/*printtree($$, 0);*/
                      		root = yyval.tptr;
			}
break;
case 2:
#line 43 "grammar.y"
{
				yyval.tptr = MakeTree(ClassOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 3:
#line 47 "grammar.y"
{
				yyval.tptr = MakeTree(ClassOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 4:
#line 52 "grammar.y"
{
				yyval.tptr = MakeTree(ClassDefOp, yyvsp[0].tptr, MakeLeaf(IDNode, yyvsp[-1].intg));
			}
break;
case 5:
#line 57 "grammar.y"
{
				if (yyvsp[-1].tptr == NullExp()) {
					yyval.tptr = yyvsp[-2].tptr;
				}
				else {
					yyval.tptr = MkLeftC(yyvsp[-2].tptr, yyvsp[-1].tptr);
				}
			}
break;
case 6:
#line 67 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 7:
#line 71 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 8:
#line 76 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 9:
#line 80 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 10:
#line 85 "grammar.y"
{
				tree headOp = MakeTree(HeadOp, MakeLeaf(IDNode, yyvsp[-4].intg), yyvsp[-2].tptr);
				yyval.tptr = MakeTree(MethodOp, headOp, yyvsp[0].tptr);
			}
break;
case 11:
#line 91 "grammar.y"
{type_tree = NullExp();}
break;
case 12:
#line 92 "grammar.y"
{
				tree headOp = MakeTree(HeadOp, MakeLeaf(IDNode, yyvsp[-4].intg), yyvsp[-2].tptr);
				yyval.tptr = MakeTree(MethodOp, headOp, yyvsp[0].tptr);
			}
break;
case 13:
#line 101 "grammar.y"
{
				yyval.tptr = type_tree = MakeTree(TypeIdOp, MakeLeaf(IDNode, yyvsp[-1].intg), yyvsp[0].tptr);
			}
break;
case 14:
#line 105 "grammar.y"
{
				yyval.tptr = type_tree = MakeTree(TypeIdOp, MakeLeaf(INTEGERTNode, yyvsp[-1].intg), yyvsp[0].tptr);
			}
break;
case 15:
#line 109 "grammar.y"
{
				tree typeTree = MakeTree(TypeIdOp, MakeLeaf(IDNode, yyvsp[-3].intg), yyvsp[-2].tptr);
				/* This code creates a tree that looks like the assignment pdf */			
				tree fieldTree = MakeTree(FieldOp, yyvsp[0].tptr, NullExp());
				yyval.tptr = type_tree = MkRightC(fieldTree, typeTree); 
				/* This code creates a tree that looks like the example parser */
				/*$$ = type_tree = MkRightC($4, typeTree);*/
			}
break;
case 16:
#line 118 "grammar.y"
{
				tree typeTree = MakeTree(TypeIdOp, MakeLeaf(INTEGERTNode, yyvsp[-3].intg), yyvsp[-2].tptr);
				/* This code creates a tree that looks like the assignment pdf */
				tree fieldTree = MakeTree(FieldOp, yyvsp[0].tptr, NullExp());
				yyval.tptr = type_tree = MkRightC(fieldTree, typeTree);
				/* This code creates a tree that looks like the example parser */
				/*$$ = type_tree = MkRightC($4, typeTree);*/
			}
break;
case 17:
#line 128 "grammar.y"
{
				yyval.tptr = type_tree = NullExp();
			}
break;
case 18:
#line 132 "grammar.y"
{
				yyval.tptr = type_tree = MakeTree(IndexOp, NullExp(), NullExp());
			}
break;
case 19:
#line 136 "grammar.y"
{
				yyval.tptr = type_tree = MakeTree(IndexOp, NullExp(), yyvsp[-2].tptr);
			}
break;
case 20:
#line 141 "grammar.y"
{
				yyval.tptr = MakeTree(SpecOp, NullExp(), type_tree);
			}
break;
case 21:
#line 145 "grammar.y"
{
				yyval.tptr = MakeTree(SpecOp, yyvsp[0].tptr, type_tree);
			}
break;
case 22:
#line 150 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 23:
#line 154 "grammar.y"
{
				yyval.tptr = MkRightC(yyvsp[0].tptr, yyvsp[-2].tptr);
			}
break;
case 24:
#line 158 "grammar.y"
{type_record = 1;}
break;
case 25:
#line 159 "grammar.y"
{
				/* This was an old approach that changed the tree if a VAL*/
				/* was found. I did not know you could take symantic actions */
				/* in the grammer matching part.*/
				/*$$ = MakeVal($3);*/
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 26:
#line 166 "grammar.y"
{type_record = 0;}
break;
case 27:
#line 167 "grammar.y"
{
				/*$$ = $2;*/
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 28:
#line 173 "grammar.y"
{
				tree idTree = MakeTree(CommaOp, MakeLeaf(IDNode, yyvsp[0].intg), MakeLeaf(INTEGERTNode, 0));
				if (type_record == 1) {
					yyval.tptr = MakeTree(VArgTypeOp, idTree, NullExp());
				} else {
					yyval.tptr = MakeTree(RArgTypeOp, idTree, NullExp());
				}
				/*$$ = MakeTree(RArgTypeOp, idTree, NullExp());*/
			}
break;
case 29:
#line 183 "grammar.y"
{
				tree idTree = MakeTree(CommaOp, MakeLeaf(IDNode, yyvsp[-2].intg), MakeLeaf(INTEGERTNode, 0));
				tree formalParameter;
				if (type_record == 1) {
					formalParameter = MakeTree(VArgTypeOp, idTree, NullExp());
				} else {
					formalParameter = MakeTree(RArgTypeOp, idTree, NullExp());
				}
				/*tree formalParameter = MakeTree(RArgTypeOp, idTree, NullExp());*/
				yyval.tptr = MkRightC(yyvsp[0].tptr, formalParameter);
			}
break;
case 30:
#line 196 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 31:
#line 200 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 32:
#line 205 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 33:
#line 210 "grammar.y"
{	
				yyval.tptr = MakeTree(StmtOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 34:
#line 214 "grammar.y"
{	
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-2].tptr;
				} else { 
					yyval.tptr = MakeTree(StmtOp, yyvsp[-2].tptr, yyvsp[0].tptr);
				}
			}
break;
case 35:
#line 223 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 36:
#line 227 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 37:
#line 231 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 38:
#line 235 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 39:
#line 239 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 40:
#line 243 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 41:
#line 248 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 42:
#line 252 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 43:
#line 258 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 44:
#line 267 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 45:
#line 271 "grammar.y"
{
				yyval.tptr = MakeTree(BodyOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 46:
#line 276 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 47:
#line 281 "grammar.y"
{
				yyval.tptr = MakeTree(DeclOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 48:
#line 285 "grammar.y"
{
				yyval.tptr = MakeTree(DeclOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 49:
#line 290 "grammar.y"
{
				tree commaTree = MakeTree(CommaOp, type_tree, NullExp());
				yyval.tptr = MakeTree(CommaOp, yyvsp[0].tptr, commaTree);
			}
break;
case 50:
#line 295 "grammar.y"
{
				tree commaTree = MakeTree(CommaOp, type_tree, yyvsp[0].tptr);
				yyval.tptr = MakeTree(CommaOp, yyvsp[-2].tptr, commaTree);
			}
break;
case 51:
#line 301 "grammar.y"
{
				yyval.tptr = MakeLeaf(IDNode, yyvsp[0].intg);
			}
break;
case 52:
#line 305 "grammar.y"
{
				yyval.tptr = MakeLeaf(IDNode, yyvsp[-1].intg);
			}
break;
case 53:
#line 310 "grammar.y"
{
				yyval.tptr = yyval.tptr;
			}
break;
case 54:
#line 314 "grammar.y"
{
				yyval.tptr = yyval.tptr;
			}
break;
case 55:
#line 319 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 56:
#line 323 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 57:
#line 327 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 58:
#line 332 "grammar.y"
{
				yyval.tptr = MakeTree(ArrayTypeOp, yyvsp[-1].tptr, type_tree);
			}
break;
case 59:
#line 337 "grammar.y"
{
				yyval.tptr = MakeTree(CommaOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 60:
#line 341 "grammar.y"
{
				yyval.tptr = MakeTree(CommaOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 61:
#line 346 "grammar.y"
{
				yyval.tptr = MakeTree(ArrayTypeOp, yyvsp[0].tptr, MakeLeaf(INTEGERTNode, yyvsp[-1].intg));
			}
break;
case 62:
#line 351 "grammar.y"
{
				yyval.tptr = MakeTree(BoundOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 63:
#line 355 "grammar.y"
{
				yyval.tptr = MakeTree(BoundOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 64:
#line 360 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 65:
#line 365 "grammar.y"
{
				tree assignOp = MakeTree(AssignOp, NullExp(), yyvsp[-2].tptr);
				yyval.tptr = MakeTree(AssignOp, assignOp, yyvsp[0].tptr);
			}
break;
case 66:
#line 371 "grammar.y"
{
				yyval.tptr = MakeTree(RoutineCallOp, yyvsp[-3].tptr, yyvsp[-1].tptr);
			}
break;
case 67:
#line 376 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 68:
#line 380 "grammar.y"
{
				yyval.tptr = MakeTree(CommaOp, yyvsp[0].tptr, NullExp());
			}
break;
case 69:
#line 384 "grammar.y"
{
				yyval.tptr = MakeTree(CommaOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 70:
#line 389 "grammar.y"
{
				yyval.tptr = MakeTree(ReturnOp, NullExp(), NullExp());
			}
break;
case 71:
#line 393 "grammar.y"
{
				yyval.tptr = MakeTree(ReturnOp, yyvsp[0].tptr, NullExp());
			}
break;
case 72:
#line 398 "grammar.y"
{
				tree commaTree = MakeTree(CommaOp, yyvsp[-1].tptr, yyvsp[0].tptr);
				yyval.tptr = MakeTree(IfElseOp, NullExp(), commaTree);
			}
break;
case 73:
#line 403 "grammar.y"
{
				tree commaTree = MakeTree(CommaOp, yyvsp[-3].tptr, yyvsp[-2].tptr);
				tree ifTree = MakeTree(IfElseOp, NullExp(), commaTree);
				yyval.tptr = MakeTree(IfElseOp, ifTree, yyvsp[0].tptr);	
			}
break;
case 74:
#line 409 "grammar.y"
{
				tree commaTree = MakeTree(CommaOp, yyvsp[-3].tptr, yyvsp[-2].tptr);
				tree ifTree = MakeTree(IfElseOp, NullExp(), commaTree);
				MkLeftC(ifTree, yyvsp[0].tptr);
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 75:
#line 417 "grammar.y"
{
				yyval.tptr = MakeTree(LoopOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 76:
#line 422 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 77:
#line 426 "grammar.y"
{
				yyval.tptr = MakeTree(LTOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 78:
#line 430 "grammar.y"
{
				yyval.tptr = MakeTree(LEOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 79:
#line 434 "grammar.y"
{
				yyval.tptr = MakeTree(EQOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 80:
#line 438 "grammar.y"
{
				yyval.tptr = MakeTree(NEOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 81:
#line 442 "grammar.y"
{
				yyval.tptr = MakeTree(GEOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 82:
#line 446 "grammar.y"
{
				yyval.tptr = MakeTree(GTOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
case 83:
#line 451 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 84:
#line 455 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 85:
#line 459 "grammar.y"
{
				yyval.tptr = yyvsp[0].tptr;
			}
break;
case 86:
#line 463 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 87:
#line 467 "grammar.y"
{
				yyval.tptr = MakeTree(NotOp, yyvsp[0].tptr, NullExp());
			}
break;
case 88:
#line 472 "grammar.y"
{
				yyval.tptr = MakeLeaf(NUMNode, yyvsp[0].intg);
			}
break;
case 89:
#line 476 "grammar.y"
{
				yyval.tptr = MakeLeaf(STRINGNode, yyvsp[0].intg);
			}
break;
case 90:
#line 481 "grammar.y"
{
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-1].tptr;
				} else {
					yyval.tptr = MkLeftC(yyvsp[-1].tptr, yyvsp[0].tptr);
				}
			}
break;
case 91:
#line 489 "grammar.y"
{
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-1].tptr;
				} else {
					yyval.tptr = MkLeftC(yyvsp[-1].tptr, yyvsp[0].tptr);
				}
			}
break;
case 92:
#line 497 "grammar.y"
{
				tree neg = MakeTree(UnaryNegOp, yyvsp[-1].tptr, NullExp());
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = neg;
				} else {
					yyval.tptr = MkLeftC(neg, yyvsp[0].tptr);
				}
			}
break;
case 93:
#line 507 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 94:
#line 511 "grammar.y"
{
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-1].tptr;
				} else {
					yyval.tptr = MkLeftC(yyvsp[-1].tptr, yyvsp[0].tptr);
				}
			}
break;
case 95:
#line 520 "grammar.y"
{
				yyval.tptr = MakeTree(AddOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 96:
#line 524 "grammar.y"
{
				yyval.tptr = MakeTree(SubOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 97:
#line 528 "grammar.y"
{
				yyval.tptr = MakeTree(OrOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 98:
#line 533 "grammar.y"
{
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-1].tptr;
				} else {
					yyval.tptr = MkLeftC(yyvsp[-1].tptr, yyvsp[0].tptr);
				}
			}
break;
case 99:
#line 542 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 100:
#line 546 "grammar.y"
{
				if (yyvsp[0].tptr == NullExp()) {
					yyval.tptr = yyvsp[-1].tptr;
				} else {
					yyval.tptr = MkLeftC(yyvsp[-1].tptr, yyvsp[0].tptr);
				}
			}
break;
case 101:
#line 555 "grammar.y"
{
				yyval.tptr = MakeTree(MultOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 102:
#line 559 "grammar.y"
{
				yyval.tptr = MakeTree(DivOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 103:
#line 563 "grammar.y"
{
				yyval.tptr = MakeTree(AndOp, NullExp(), yyvsp[0].tptr);
			}
break;
case 104:
#line 568 "grammar.y"
{
				yyval.tptr = MakeTree(VarOp, MakeLeaf(IDNode, yyvsp[-1].intg), yyvsp[0].tptr);
			}
break;
case 105:
#line 573 "grammar.y"
{
				yyval.tptr = NullExp();
			}
break;
case 106:
#line 577 "grammar.y"
{
				yyval.tptr = MakeTree(SelectOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 107:
#line 581 "grammar.y"
{
				yyval.tptr = MakeTree(SelectOp, yyvsp[-1].tptr, yyvsp[0].tptr);
			}
break;
case 108:
#line 586 "grammar.y"
{
				yyval.tptr = MakeTree(FieldOp, MakeLeaf(IDNode, yyvsp[0].intg), NullExp());
			}
break;
case 109:
#line 591 "grammar.y"
{
				yyval.tptr = yyvsp[-1].tptr;
			}
break;
case 110:
#line 596 "grammar.y"
{
				yyval.tptr = MakeTree(IndexOp, yyvsp[0].tptr, NullExp());
			}
break;
case 111:
#line 600 "grammar.y"
{
				yyval.tptr = MakeTree(IndexOp, yyvsp[-2].tptr, yyvsp[0].tptr);
			}
break;
#line 1337 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    return (1);

yyaccept:
    return (0);
}
