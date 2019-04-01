CS 1622 Compilers Project 3
Brian Lester bdl20@pitt.edu 4-25-16

This is my Project for CS 1622 Semantic Analysis
The Semantic Analyzer code is in seman.c
The project can be compiled as follows:
	make
This will run a make file that runs the commands
	flex lex.l (generates lex.yy.c)
	yacc -v grammar.y (generates y.tab.c)
	gcc -g -o seman seman.c y.tab.c proj2.c proj3.c -lfl
This analyzer can then be run on files with the command
	./seman < file
This was compiled and tested on my computer running gcc version 4.8.4

This project is based on my projects 1 and 2 and therefore uses my string
table created in project 1. As such some of the indexes for strings and 
variable names into the string table may be different than that of the 
example. In a similar vain my STRINGNodes do not contain the quotes while 
the example does.

This is also based on my project 2 so the differences between my parse 
tree and the examples is shown here due to the example from the course
website generates trees that are different than the ones in the .pdf.
	
These examples are copied from my proj2 readme.txt

This in seen in the file ex8 where the program input looks like so

program xyz;
class test{
	declarations
	enddeclarations
}

The example parser generates the following tree:
************* SYNTAX TREE PRINTOUT ***********

  +-[IDNode,0,"xyz"]
R-[ProgramOp]
  |   +-[IDNode,4,"test"]
  | +-[ClassDefOp]
  | | | +-[DUMMYnode]
  | | +-[BodyOp]
  | |   +-[DUMMYnode]
  +-[ClassOp]
    +-[DUMMYnode]

However the Tree by the assignment should look like so:
************* SYNTAX TREE PRINTOUT ***********

  +-[IDNode,0,"xyz"]
R-[ProgramOp]
  |   +-[IDNode,4,"test"]
  | +-[ClassDefOp]
  | | +-[DUMMYnode]
  +-[ClassOp]
    +-[DUMMYnode]

This is by the definitions of the ClassDecl tree. The left 
child of the ClassDecl is the subtree for the ClassBody. If 
there is no method declares then the ClassBody subtree is 
just the Decls subtree. There are also no FieldDecls which means
that the Decls subtree is just a DUMMYnode. This means that the
ClassBody subtree is also just a DUMMYnode. Therefore the left 
child of the ClassDefOp should just be a DUMMYnode rather than a 
BodyOp node with DUMMYnodes as the left and right children. 


The is also seen for the Type declarations:
With the following example Type declaration
	int[].field[] 
The example parser creates the wrong tree. 
The example parser generates the following tree section:
  | | | | |           +-[DUMMYnode]
  | | | | |         +-[IndexOp]
  | | | | |         | +-[DUMMYnode]
  | | | | |       +-[TypeIdOp]
  | | | | |       | +-[IDNode,10,"field"]
  | | | | |     +-[IndexOp]
  | | | | |     | +-[DUMMYnode]
  | | | | |   +-[TypeIdOp]
  | | | | |   | +-[INTEGERTNode]
My parser generates the following tree section:
  | | | | |         +-[DUMMYnode]
  | | | | |       +-[FieldOp]
  | | | | |       | |   +-[DUMMYnode]
  | | | | |       | | +-[IndexOp]
  | | | | |       | | | +-[DUMMYnode]
  | | | | |       | +-[TypeIdOp]
  | | | | |       |   +-[IDNode,10,"field"]
  | | | | |     +-[IndexOp]
  | | | | |     | +-[DUMMYnode]
  | | | | |   +-[TypeIdOp]
  | | | | |   | +-[INTEGERTNode]
This is the correct tree as you can see from the Type tree from
the assignment pdf. You can see that when there is a field there
should be a FieldOp with a DUMMYNode as the right child and another
Type tree should be the left child. The example parser is not correct 
as when it encounters a field it adds it as a right child of the last 
IndexOp node rather than creating a new FieldOp node.

Dr. Zhang told me to include these cases where my parse did different 
things than the example parser (When my version is correct and the 
example is wrong) so that the grader knows about these cases. 

There are also a few more differences. My parse tree includes an IDNode 
that holds the programs name rather than a dummy node. This node is not 
used so the choice to leave it is acceptable. 

My analyzer also uses some more specific error messages. Namely it uses
an undeclared field name rather than just undeclared and it uses a 
special error message if main is redefined rather than the standard one.

My Semantic analyzer also catches two errors that the example does not. It 
catches the number of args in the use of a function do not match with the 
number of parameters used in the method declaration. It also catches when
a string constant is used outside of an output function.