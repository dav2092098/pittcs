#include <stdio.h>
#include <string.h>
#include "proj2.h"
#include "proj3.h"
#include "table.h"

extern FILE *treelst;
extern tree root;
extern int error;

int outputMethod = 0;

void traversetree();
void inorder(tree root);
void process(tree root);
void process_node(tree root);
void process_leaf(tree root);
void analyze_ClassOp(tree root);
void analyze_BodyOp(tree root);
void analyze_DeclOp(tree root);
void analyze_MethodOp(tree root);
void analyze_Arg(tree root);
void analyze_Stmt(tree root);
void analyze_AssignOp(tree root);
int analyze_Var(tree root);
void analyze_Exp(tree root);
void analyze_SimpleExp(tree root);
void analyze_RoutineCallOp(tree root);
void analyze_Term(tree root);
void analyze_Factor(tree root);
void analyze_Array(tree root, int dimension, int arr);
void analyze_VarInt(tree root, int dimension, int arr);
void analyze_ArrayInit(tree root, int dimension, int arr);
void analyze_ArrayCreate(tree root, int dimension, int arr);
void analyze_ReturnOp(tree root);
void analyze_LoopOp(tree root);
void analyze_IfElseOp(tree root);
int count_Args(tree root);
void bottomUp(tree root);
void topDownLeft(tree root);
void topDownRight(tree root);
int countDimension(tree root);

int main() {
	treelst = stdout;
	yyparse();
	if (error != 1) {
		//print_string_table();
		STInit();
		traversetree();
		STPrint();
		printtree(root, 0);
		return 0;
	}
	puts("Syntax Tree not created, exiting...");
	return 1;
}

void traversetree() {
	bottomUp(root);
}

// Analyze nodes using a left recursive strategy 
// process the nodes on the way back up.
void bottomUp(tree root) {
	if (IsNull(root)) {
		return;
	}
	bottomUp(LeftChild(root));
	process(root);
}

// Analyze nodes using a left recursive strategy
// process the nodes on the way down
void topDownLeft(tree root) {
	if (IsNull(root)) {
		return;
	}
	process(root);
	topDownLeft(LeftChild(root));
}

// Analyze Nodes using a right recursive strategy
// process nodes on the way down
void topDownRight(tree root) {
	if (IsNull(root)) {
		return;
	}
	process(root);
	topDownRight(RightChild(root));
}

// process the node depending on the type
void process(tree root) {
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root))
		{
			case ClassOp:
				analyze_ClassOp(root);
				break;
			case BodyOp:
				analyze_BodyOp(root);
				break;
			case DeclOp:
				analyze_DeclOp(root);
				break;
			case RArgTypeOp:
			case VArgTypeOp:
				analyze_Arg(root);
				break;
			case StmtOp:
				analyze_Stmt(root);
				break;
			// Used when analyzing function args
			case CommaOp:
				analyze_Exp(LeftChild(root));
				break;
			// Used when analyzing Array Creation Expression
			case BoundOp:
				analyze_Exp(RightChild(root));
				break;
			default:
				break;
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze a class in the program
void analyze_ClassOp(tree root) {
	int id, nSymInd;
	// Grab the ClassDefOp Node
	tree node = RightChild(root);
	if (NodeKind(node) == EXPRNode) {
		if (NodeOp(node) == ClassDefOp) {
			tree classname = RightChild(node);
			if (NodeKind(classname) == EXPRNode) {
				return;
			}
			id = IntVal(classname);
			// Look Up the class
			nSymInd = InsertEntry(id);
			// Insert class info
			SetAttr(nSymInd, KIND_ATTR, CLASS);
			// Transform the IDnode
			SetNodeKind(classname, STNode);
			SetIntVal(classname, nSymInd);
			tree body = LeftChild(node);
			// Open a new nesting level (scope)
			OpenBlock();
			// recursivly analyze what will be BodyOp Nodes
			bottomUp(node);
			// Close scope
			CloseBlock();
		}
	}
}

// Analyze a Body Node
void analyze_BodyOp(tree root) {
	tree node = RightChild(root);
	if (NodeKind(node) == EXPRNode) {
		switch(NodeOp(node))
		{
			case DeclOp:
				// Analyze all the Decls untill Dummy
				topDownLeft(node);
				break;
			case MethodOp:
				analyze_MethodOp(node);
				break;
			case StmtOp:
				// Analyze all Stmt recursivly
				bottomUp(node);
				break;
			default:
				break;
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze Method
// The node passed in is the MethodOp Node
void analyze_MethodOp(tree root) {	
	// Add the name
	tree name = LeftChild(LeftChild(root));
	int nSymInd = InsertEntry(IntVal(name));
	if (nSymInd == -1) {
		return;
	}
	// Transform the node
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);
	// fetch the type tree
	tree type = RightChild(RightChild(LeftChild(root)));
	if (IsNull(type)) {
		// If there is no type then it is void and a procedure
		SetAttr(nSymInd, KIND_ATTR, PROCE);	
	} else {
		// if there is a type it is a function and save the type
		SetAttr(nSymInd, KIND_ATTR, FUNC);	
		SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)type); 
	}
	// Open a new scope
	OpenBlock();
	// Prase arguments
	// Count the number or arguments
	int numArgs = count_Args(LeftChild(RightChild(LeftChild(root))));
	// Analyze each argument
	topDownRight(LeftChild(RightChild(LeftChild(root))));
	// set the number or agrs
	SetAttr(nSymInd, ARGNUM_ATTR, numArgs);
	// analyze the statements
	bottomUp(RightChild(root));
	// close scope
	CloseBlock();
}	

// Count The number of args in the method
int count_Args(tree root) {
	if (IsNull(root)) {
		return 0;
	}
	//analyze_Arg(root);
	return count_Args(RightChild(root)) + 1;
}

// Analyze a VArgTypeOp or RArgType
// The node passed in is the R/VArgNode
void analyze_Arg(tree root) {
	tree name = LeftChild(LeftChild(root));
	tree type = RightChild(LeftChild(root));
	// Insert the arg
	int nSymInd = InsertEntry(IntVal(name));
	// Set it to a Value arg or reference arg
	if (NodeOp(root) == RArgTypeOp) {
		SetAttr(nSymInd, KIND_ATTR, REF_ARG);
	} else {
		SetAttr(nSymInd, KIND_ATTR, VALUE_ARG);
	} 
	// Set the type
	SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)type);
	// Transform the node
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);
}

// Analyze a DeclOp
// the DeclOp is passed in
void analyze_DeclOp(tree root) {
	int id, nSymInd;	
	int dimension = 0;
	// Variable to declare
	tree name = LeftChild(RightChild(root));
	id = IntVal(name);
	nSymInd = InsertEntry(id);
	if (nSymInd == 0) {
		return;
	}
	SetAttr(nSymInd, KIND_ATTR, VAR);
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);
	// Type Stuff
	tree typeTree = LeftChild(RightChild(RightChild(root)));
	SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)typeTree);
	tree type = LeftChild(typeTree);
	if (NodeKind(type) == IDNode) {
		int typeIndex = IntVal(type);
		int typeSymInd = LookUp(typeIndex);
		SetNodeKind(type, STNode);
		SetIntVal(type, typeSymInd);
	}
	// Array Stuff
	dimension = countDimensions(RightChild(typeTree));
	// Set the number of dimensions for arrays
	if (dimension != 0) {
		SetAttr(nSymInd, KIND_ATTR, ARR);
		SetAttr(nSymInd, DIMEN_ATTR, dimension);
	}
	tree varInt = RightChild(RightChild(RightChild(root)));
	// Analyze if the var's are being initialized
	analyze_VarInt(varInt, dimension, nSymInd);
}

// Analyze var initilizations
void analyze_VarInt(tree root, int dimension, int arr) {
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		// If it is an array check the bounds
		if (NodeOp(root) == ArrayTypeOp) {
			analyze_Array(root, dimension, arr);
		} else {
			// if it is a normal var it is just an expression
			analyze_Exp(root);
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze if an array is initalized
void analyze_Array(tree root, int dimension, int arr) {
	tree start = LeftChild(root);
	if (IsNull(start)) {
		return;
	}
	// if there are Comma nodes it is an Array Initilization
	if (NodeOp(start) == CommaOp) {
		analyze_ArrayInit(start, dimension, arr);
	// else there itis an Array Creation
	} else {
		analyze_ArrayCreate(start, dimension, arr);
	}
}

// analyze an array initilization
void analyze_ArrayInit(tree root, int dimension, int arr) {
	if (IsNull(root)) {
		return;
	}
	// recurse to the last one
	analyze_ArrayInit(LeftChild(root), dimension, arr);
	// analyze the var initializeation
	analyze_VarInt(RightChild(root), dimension, arr);
}

// analyze the creation of an array
void analyze_ArrayCreate(tree root, int dimension, int arr) {
	int dimensions = countDimensionsLeft(root);
	// the dimensions are incorrect report error
	if (dimensions != dimension) {
		error_msg(
			INDX_MIS, 
			CONTINUE,
			GetAttr(arr, NAME_ATTR), 
			0);
	}
	bottomUp(root);
}

// recursivly count the number of nodes to the right before a Dummy
int countDimensions(tree root) {
	if (IsNull(root)) {
		return 0;
	}
	return countDimensions(RightChild(root)) + 1;
}

// recurisvly count the number of nodes to the left before a Dummy
int countDimensionsLeft(tree root) {
	if (IsNull(root)) {
		return 0;
	}
	return countDimensionsLeft(LeftChild(root)) + 1;
}

// Analyze a Statement
void analyze_Stmt(tree root) {
	tree op = RightChild(root);
	if (IsNull(op)) {
		return;
	}
	if (NodeKind(op) != EXPRNode) {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
	switch (NodeOp(op)) 
	{
		case AssignOp:
			analyze_AssignOp(op);
			break;
		case RoutineCallOp:
			analyze_RoutineCallOp(op);
			break;
		case ReturnOp:
			analyze_ReturnOp(op);
			break;
		case IfElseOp:
			analyze_IfElseOp(op);
			break;
		case LoopOp:
			analyze_LoopOp(op);
			break;
		default:
			break;
	}
}

// Analyze an IfElse Construct
void analyze_IfElseOp(tree root) {
	if (IsNull(root)) {
		return;
	}
	// recurse to the bottom of the IfElse trees
	analyze_IfElseOp(LeftChild(root));
	if (NodeOp(RightChild(root)) == CommaOp) {	
		// Comma Tree
		// (This is used on 'if' and 'else if'
		// Analyze the Exp
		analyze_Exp(LeftChild(RightChild(root)));
		// Analyze the statement list
		bottomUp(RightChild(RightChild(root)));
	}
	// analyze the statements to the right (final else block)
	if (NodeOp(RightChild(root)) == StmtOp) {
		bottomUp(RightChild(root));
	}
}

// Analyze a return
void analyze_ReturnOp(tree root) {
	if (!IsNull(LeftChild(root))) {
		analyze_Exp(LeftChild(root));
	}
}

// Analyze a loop
void analyze_LoopOp(tree root) {
	analyze_Exp(LeftChild(root));
	bottomUp(RightChild(root));
}

// Analyze an Assignment
void analyze_AssignOp(tree root) {
	tree var = RightChild(LeftChild(root));
	analyze_Var(var);
	tree exp = RightChild(root);
	analyze_Exp(exp);
	// For use when type checking
	/*
	int lhs = analyze_Var(var);
	int rhs = analyze_Exp(exp);
	if (IsAttr(lhs, TYPE_ATTR) && IsAttr(rhs, TYPE_ATTR)) {
		check and compare types
		if not equal
			error_msg(
				TYPE_MIS,
				CONTINUE,
				rhs,
				lhs);		
	} */
}

/*
Currently the tree is like 
	select
	/		\
  index		select
			/	\...
			index

rather than
	select
	/		\
	index
	/	\
	Exp	 index
		 /   \
		Exp   Dum

I should fix this grammer
*/
// Returns the index of the var
int analyze_Var(tree root) {
	if (NodeKind(root) != EXPRNode) {
		return;
	}
	// Analyse the name of the var
	tree name = LeftChild(root);
	int nSymInd = LookUp(IntVal(name));
	if (nSymInd == 0) {
		return 0;
	}
	//int kind = GetAttr(nSymInd, KIND_ATTR);
	// Set it to a symbol table node
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);
	// Find if the var is a class (Directly like Test.field or 
	// indirectly like Test t; t.field
	int classIndex = findClass(nSymInd);
	int usedDim = 0;
	tree select = RightChild(root);
	// Iterate through the select sub tree
	while (!IsNull(select)) {
		if (NodeOp(LeftChild(select)) == IndexOp) {
			// Used in the correct parse tree
			// int usedDim = countDimensions(LeftChild(select));
			// topDownRight(LeftChild(select));
			
			// If there is an index node increment index count
			usedDim += 1;
			// If the variable or previous field is not an array 
			// then report an error
			if (IsAttr(nSymInd, KIND_ATTR)) {			
				if (GetAttr(nSymInd, KIND_ATTR) != ARR) {
					error_msg(
						ARR_TYPE_MIS, 
						CONTINUE, 
						GetAttr(nSymInd, NAME_ATTR),
						0);
					select = RightChild(select);
					continue;
				}
			}

			// Used in the correct parse tree
			//if (usedDim != GetAttr(element, DIMEN_ATTR)) {
			//	error_msg(
			//		ARR_DIME_MIS, 
			//		CONTINUE, 
			//		GetAttr(element, NAME_ATTR), 
			//		0);
			//}

			// Analyze the expression in the index
			analyze_Exp(LeftChild(LeftChild(select)));
		} 
		if (NodeOp(LeftChild(select)) == FieldOp) {
			// If the previous var or field is not a class then 
			// report an error, it shouldn't have a field
			if (classIndex == -1) {
				error_msg(
					TYPE_MIS,
					CONTINUE,
					GetAttr(nSymInd, NAME_ATTR), 
					0);
				return 0;
			}

			// Move this up if I rewrite the grammer	
			// Check if the previous var matched the dimensions
			//if (GetAttr(element, KIND_ATTR) == ARR) {		
			//	if (usedDim != GetAttr(element, DIMEN_ATTR)) {
			//		error_msg(
			//			ARR_DIME_MIS, 
			//			CONTINUE, 
			//			GetAttr(element, NAME_ATTR), 
			//			0);
			//	}
			//}

			// Grab the field name node
			tree fieldName = LeftChild(LeftChild(select));
			// Look up and find the one in the right scope
			nSymInd = LookUpField(classIndex, IntVal(fieldName));
			if (nSymInd == 0) {
				return 0;
			}
			SetNodeKind(fieldName, STNode);
			SetIntVal(fieldName, nSymInd);
			// Find class index of the field
			classIndex = findClass(nSymInd);
			usedDim = 0;
		}
		// grab next node for loop
		select = RightChild(select);
	}  
	// Compare the number of index's with the number it had. This only
	// works on the last field because all fields should be classes 
	// because we can't have an array of classes
	if (IsAttr(nSymInd, KIND_ATTR)) {
		if (GetAttr(nSymInd, KIND_ATTR) == ARR) {
			if (usedDim != GetAttr(nSymInd, DIMEN_ATTR)) {
				error_msg(
					INDX_MIS, 
					CONTINUE, 
					GetAttr(nSymInd, NAME_ATTR), 
					0);
			}
		}
	}
	return nSymInd;
}

// Analyze an Expression
void analyze_Exp(tree root) {
	if (NodeKind(root) == EXPRNode) {
		switch(NodeOp(root))
		{
			case LTOp:
			case LEOp:
			case EQOp:
			case NEOp:
			case GEOp:
			case GTOp:
				analyze_SimpleExp(LeftChild(root));
				analyze_SimpleExp(RightChild(root));
				break;
			default:
				analyze_SimpleExp(root);
				break;
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze a simple expression
void analyze_SimpleExp(tree root) {
	int last = 0;
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case AddOp:
			case SubOp:
			case OrOp:
				analyze_SimpleExp(LeftChild(root));
				break;
			case UnaryNegOp:
				last = 1;
				analyze_Term(LeftChild(root));
				break;
			default:
				last = 1;
				analyze_Term(root);
				break;
		}
		if (last == 0) {
			analyze_Term(RightChild(root));
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze a Term
void analyze_Term(tree root) {
	int last = 0;
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case MultOp:
			case DivOp:
			case AndOp:
				analyze_Term(LeftChild(root));
				break;
			default:
				last = 1;
				analyze_Factor(root);
				break;
		}
		if (last == 0) {
			analyze_Factor(RightChild(root));
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze a Factor
void analyze_Factor(tree root) {
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case VarOp:
				analyze_Var(root);
				break;
			case RoutineCallOp:
				analyze_RoutineCallOp(root);
				break;
			// Error?m
			default:
				analyze_Exp(root);
				break;
		}
	}
	else {
		if (NodeKind(root) == STRINGNode) {
			if (outputMethod == 0) {
				error_msg(
					STRING_MIS,
					CONTINUE,
					IntVal(root),
					0);
			}
		}
	}
}

// Analyze a Rountine Call
// Add type checking?
void analyze_RoutineCallOp(tree root) {
	tree var = LeftChild(root);	
	int name = analyze_Var(var);
	if (name == 0) {
		return;
	}
	// Set a global to mark if we are currently using an output function
	if (!strcmp(getname(GetAttr(name, NAME_ATTR)), "println")) {
		outputMethod = 1;
	}
	// If this is not a procedure or function report error
	if (GetAttr(name, KIND_ATTR) != FUNC
			&& GetAttr(name, KIND_ATTR) != PROCE) {
		error_msg(
			PROCE_MISMATCH,
			CONTINUE,
			GetAttr(name, NAME_ATTR),
			0);
		return;
	}
	// check the argument numbers
	int args = countDimensions(RightChild(root));
	if (IsAttr(name, ARGNUM_ATTR)) { 
		if (args != GetAttr(name, ARGNUM_ATTR)) {
			error_msg(
				ARGUMENTS_NUM2,
				CONTINUE,
				GetAttr(name, NAME_ATTR),
				0);
			return;
		}
	}
	// Analyze the arguments
	topDownRight(RightChild(root));
	outputMethod = 0;
}
