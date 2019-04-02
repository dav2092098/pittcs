#include <stdio.h>
#include <string.h>
#include "proj2.h"
#include "proj3.h"
#include "strtable.h"

extern FILE *treelst;
extern tree root;
extern int error;

int outputMethod = 0;

void traversetree();
void inorder(tree root);
void process(tree root);
void process_node(tree root);
void process_leaf(tree root);
void chk_ClassOp(tree root);
void chk_BodyOp(tree root);
void chk_DeclOp(tree root);
void chk_MethodOp(tree root);
void chk_Arg(tree root);
void chk_Stmt(tree root);
void chk_AssignOp(tree root);
void chk_Exp(tree root);
void chk_Array(tree root, int dimension, int arr);
void chk_VarInt(tree root, int dimension, int arr);
void chk_ArrayInit(tree root, int dimension, int arr);
void chk_ArrayCreate(tree root, int dimension, int arr);
void chk_ReturnOp(tree root);
void chk_LoopOp(tree root);
void chk_IfElseOp(tree root);
void bottomUp(tree root);
void topDownLeft(tree root);
void topDownRight(tree root);
void chk_SimpleExp(tree root);
void chk_Term(tree root);
void chk_Factor(tree root);
void chk_RoutineCallOp(tree root);

int countDimension(tree root);
int chk_Var(tree root);

int main() {
	treelst = stdout;
	yyparse();
	if (error != 1) {
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

void bottomUp(tree root) {
	if (IsNull(root)) {
		return;
	}
	bottomUp(LeftChild(root));
	process(root);
}

void topDownLeft(tree root) {
	if (IsNull(root)) {
		return;
	}
	process(root);
	topDownLeft(LeftChild(root));
}

void topDownRight(tree root) {
	if (IsNull(root)) {
		return;
	}
	process(root);
	topDownRight(RightChild(root));
}

void process(tree root) {
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root))
		{
			case ClassOp:
				chk_ClassOp(root);
				break;
			case BodyOp:
				chk_BodyOp(root);
				break;
			case DeclOp:
				chk_DeclOp(root);
				break;
			case RArgTypeOp:
			case VArgTypeOp:
				chk_Arg(root);
				break;
			case StmtOp:
				chk_Stmt(root);
				break;
			case CommaOp:
				chk_Exp(LeftChild(root));
				break;			
			case BoundOp:
				chk_Exp(RightChild(root));
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

/*==== Class semantics ====*/
void chk_ClassOp(tree root) {
	int id, nSymInd;
	tree node = RightChild(root);
	if (NodeKind(node) == EXPRNode) {
		if (NodeOp(node) == ClassDefOp) {
			tree classname = RightChild(node);
			if (NodeKind(classname) == EXPRNode) {
				return;
			}

			id = IntVal(classname);			
			nSymInd = InsertEntry(id);

			SetAttr(nSymInd, KIND_ATTR, CLASS);			
			SetNodeKind(classname, STNode);
			SetIntVal(classname, nSymInd);

			tree body = LeftChild(node);
			
			OpenBlock();			
			bottomUp(node);
			CloseBlock();
		}
	}
}

void chk_BodyOp(tree root) {
	tree node = RightChild(root);
	if (NodeKind(node) == EXPRNode) {
		switch(NodeOp(node))
		{
			case DeclOp:				
				topDownLeft(node);
				break;
			case MethodOp:
				chk_MethodOp(node);
				break;
			case StmtOp:				
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
/*==== End Class semantics ====*/

/*==== Method semantics ====*/
void chk_MethodOp(tree root) {		
	tree name = LeftChild(LeftChild(root));
	int nSymInd = InsertEntry(IntVal(name));

	if (nSymInd == -1) {
		return;
	}

	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);	
	tree type = RightChild(RightChild(LeftChild(root)));

	if (IsNull(type)) {
		
		SetAttr(nSymInd, KIND_ATTR, PROCE);	
	} else {		
		SetAttr(nSymInd, KIND_ATTR, FUNC);	
		SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)type); 
	}
	
	OpenBlock();	
	int numArgs = count_Args(LeftChild(RightChild(LeftChild(root))));	
	topDownRight(LeftChild(RightChild(LeftChild(root))));	
	SetAttr(nSymInd, ARGNUM_ATTR, numArgs);	
	bottomUp(RightChild(root));	
	CloseBlock();
}	

int count_Args(tree root) {
	if (IsNull(root)) {
		return 0;
	}	
	return count_Args(RightChild(root)) + 1;
}

void chk_Arg(tree root) {
	tree name = LeftChild(LeftChild(root));
	tree type = RightChild(LeftChild(root));	
	int nSymInd = InsertEntry(IntVal(name));
	
	if (NodeOp(root) == RArgTypeOp) {
		SetAttr(nSymInd, KIND_ATTR, REF_ARG);
	} else {
		SetAttr(nSymInd, KIND_ATTR, VALUE_ARG);
	} 
	
	SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)type);	
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);
}
/*==== End Method semantics ====*/

/*==== Var declaration semantics ====*/
void chk_DeclOp(tree root) {
	int id, nSymInd;	
	int dimension = 0;	
	tree name = LeftChild(RightChild(root));
	id = IntVal(name);
	nSymInd = InsertEntry(id);

	if (nSymInd == 0) {
		return;
	}
	SetAttr(nSymInd, KIND_ATTR, VAR);
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);

	/*==== Type checking ====*/
	tree typeTree = LeftChild(RightChild(RightChild(root)));
	SetAttr(nSymInd, TYPE_ATTR, (uintptr_t)typeTree);
	tree type = LeftChild(typeTree);
	if (NodeKind(type) == IDNode) {
		int typeIndex = IntVal(type);
		int typeSymInd = LookUp(typeIndex);
		SetNodeKind(type, STNode);
		SetIntVal(type, typeSymInd);
	}
	/*==== End Type checking ====*/
	

	dimension = countDimensions(RightChild(typeTree));

	if (dimension != 0) {
		SetAttr(nSymInd, KIND_ATTR, ARR);
		SetAttr(nSymInd, DIMEN_ATTR, dimension);
	}

	tree varInt = RightChild(RightChild(RightChild(root)));	
	chk_VarInt(varInt, dimension, nSymInd);
}
/*==== End Var declaration semantics ====*/

/*==== Var-Int semantics ====*/
void chk_VarInt(tree root, int dimension, int arr) {
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {		
		if (NodeOp(root) == ArrayTypeOp) {
			chk_Array(root, dimension, arr);
		} else {			
			chk_Exp(root);
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
/*==== End Var-Int semantics ====*/

/*==== Array semantics ====*/
void chk_Array(tree root, int dimension, int arr) {
	tree start = LeftChild(root);
	if (IsNull(start)) {
		return;
	}
	
	if (NodeOp(start) == CommaOp) {
		chk_ArrayInit(start, dimension, arr);	
	} else {
		chk_ArrayCreate(start, dimension, arr);
	}
}

void chk_ArrayInit(tree root, int dimension, int arr) {
	if (IsNull(root)) {
		return;
	}
	
	chk_ArrayInit(LeftChild(root), dimension, arr);	
	chk_VarInt(RightChild(root), dimension, arr);
}

void chk_ArrayCreate(tree root, int dimension, int arr) {
	int dimensions = countDimensionsLeft(root);	
	if (dimensions != dimension) {
		error_msg(
			INDX_MIS, 
			CONTINUE,
			GetAttr(arr, NAME_ATTR), 
			0);
	}
	bottomUp(root);
}
/*==== End Array semantics ====*/

int countDimensions(tree root) {
	if (IsNull(root)) {
		return 0;
	}
	return countDimensions(RightChild(root)) + 1;
}

int countDimensionsLeft(tree root) {
	if (IsNull(root)) {
		return 0;
	}
	return countDimensionsLeft(LeftChild(root)) + 1;
}

/*==== Statement semantics ====*/
void chk_Stmt(tree root) {
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
			chk_AssignOp(op);
			break;
		case RoutineCallOp:
			chk_RoutineCallOp(op);
			break;
		case ReturnOp:
			chk_ReturnOp(op);
			break;
		case IfElseOp:
			chk_IfElseOp(op);
			break;
		case LoopOp:
			chk_LoopOp(op);
			break;
		default:
			break;
	}
}
/*==== End Statement semantics ====*/

/*==== If-Else semantics ====*/
void chk_IfElseOp(tree root) {
	if (IsNull(root)) {
		return;
	}
	
	chk_IfElseOp(LeftChild(root));
	if (NodeOp(RightChild(root)) == CommaOp) {			
		chk_Exp(LeftChild(RightChild(root)));		
		bottomUp(RightChild(RightChild(root)));
	}
	
	if (NodeOp(RightChild(root)) == StmtOp) {
		bottomUp(RightChild(root));
	}
}
/*==== End If-Else semantics ====*/

/*==== Return semantics ====*/
void chk_ReturnOp(tree root) {
	if (!IsNull(LeftChild(root))) {
		chk_Exp(LeftChild(root));
	}
}
/*==== End Return semantics ====*/

/*==== Loop semantics ====*/
void chk_LoopOp(tree root) {
	chk_Exp(LeftChild(root));
	bottomUp(RightChild(root));
}
/*==== End Loop semantics ====*/

/*==== Assignment semantics ====*/
void chk_AssignOp(tree root) {
	tree var = RightChild(LeftChild(root));
	chk_Var(var);
	tree exp = RightChild(root);
	chk_Exp(exp);
}
/*==== End Assignment semantics ====*/


/*==== Var semantics ====*/
int chk_Var(tree root) {
	if (NodeKind(root) != EXPRNode) {
		return;
	}
	
	tree name = LeftChild(root);
	int nSymInd = LookUp(IntVal(name));
	if (nSymInd == 0) {
		return 0;
	}
	
	SetNodeKind(name, STNode);
	SetIntVal(name, nSymInd);	
	int classIndex = findClass(nSymInd);
	int usedDim = 0;

	tree select = RightChild(root);
	
	while (!IsNull(select)) {
		if (NodeOp(LeftChild(select)) == IndexOp) {			
			usedDim += 1;

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
			chk_Exp(LeftChild(LeftChild(select)));
		} 
		if (NodeOp(LeftChild(select)) == FieldOp) {			
			if (classIndex == -1) {
				error_msg(
					TYPE_MIS,
					CONTINUE,
					GetAttr(nSymInd, NAME_ATTR), 
					0);
				return 0;
			}
			
			tree fieldName = LeftChild(LeftChild(select));			
			nSymInd = LookUpField(classIndex, IntVal(fieldName));
			
			if (nSymInd == 0) {
				return 0;
			}

			SetNodeKind(fieldName, STNode);
			SetIntVal(fieldName, nSymInd);
			
			classIndex = findClass(nSymInd);
			usedDim = 0;
		}
		
		select = RightChild(select);
	}  
	
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
/*==== End Var semantics ====*/

/*==== Expression semantics ====*/
void chk_Exp(tree root) {
	if (NodeKind(root) == EXPRNode) {
		switch(NodeOp(root))
		{
			case LTOp:
			case LEOp:
			case EQOp:
			case NEOp:
			case GEOp:
			case GTOp:
				chk_SimpleExp(LeftChild(root));
				chk_SimpleExp(RightChild(root));
				break;
			default:
				chk_SimpleExp(root);
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

void chk_SimpleExp(tree root) {
	int last = 0;
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case AddOp:
			case SubOp:
			case OrOp:
				chk_SimpleExp(LeftChild(root));
				break;
			case UnaryNegOp:
				last = 1;
				chk_Term(LeftChild(root));
				break;
			default:
				last = 1;
				chk_Term(root);
				break;
		}
		if (last == 0) {
			chk_Term(RightChild(root));
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
/*==== End expression semantics ====*/

/*==== Term semantics ====*/
void chk_Term(tree root) {
	int last = 0;
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case MultOp:
			case DivOp:
			case AndOp:
				chk_Term(LeftChild(root));
				break;
			default:
				last = 1;
				chk_Factor(root);
				break;
		}
		if (last == 0) {
			chk_Factor(RightChild(root));
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
/*==== End Term semantics ====*/

/*==== Factor semantics ====*/
void chk_Factor(tree root) {
	if (IsNull(root)) {
		return;
	}
	if (NodeKind(root) == EXPRNode) {
		switch (NodeOp(root)) {
			case VarOp:
				chk_Var(root);
				break;
			case RoutineCallOp:
				chk_RoutineCallOp(root);
				break;
			default:
				chk_Exp(root);
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
/*==== End Term semantics ====*/

/*==== Function call semantics ====*/
void chk_RoutineCallOp(tree root) {
	tree var = LeftChild(root);	
	int name = chk_Var(var);
	if (name == 0) {
		return;
	}
	
	if (!strcmp(getname(GetAttr(name, NAME_ATTR)), "println")) {
		outputMethod = 1;
	}
	
	if (GetAttr(name, KIND_ATTR) != FUNC
			&& GetAttr(name, KIND_ATTR) != PROCE) {
		error_msg(
			PROCE_MISMATCH,
			CONTINUE,
			GetAttr(name, NAME_ATTR),
			0);
		return;
	}
	
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
	
	topDownRight(RightChild(root));
	outputMethod = 0;
}
/*==== End Function call semantics ====*/
