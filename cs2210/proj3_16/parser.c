#include <stdio.h>
#include "proj2.h"
#include "proj3.h"

extern FILE *treelst;
extern tree root;
extern int error;

main()
{
	treelst = stdout;
	yyparse();
	if (error == 0) {
		printtree(root, 0);
	}
}
