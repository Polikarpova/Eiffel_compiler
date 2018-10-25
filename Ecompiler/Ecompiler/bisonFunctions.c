#include <tree_structs.h>
#include <stdlib.h>
#include <string>

struct NExpr* createIntConstExpr (int token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = IntE;
	Result->value.Int = token;

	return Result;
}

struct NExpr* createRealConstExpr (double token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
	Result->type = RealE;
	Result->value.Real = token;

	return Result;
}

struct NExpr* createCharConstExpr (char token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = CharE;
	Result->value.Char = token;

	return Result;
}

struct NExpr* createStringConstExpr (char* token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = IntE;
	strcpy(Result->value.String, token);

	return Result;
}

struct NExpr* createBoolConstExpr (bool token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = BoolE;
	Result->value.Bool = token;

	return Result;
}

struct NExpr* createRefExpr (struct NRefChain* ref)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = RefE;
	Result->value.ref = ref;

	return Result;
}

struct NExpr* createExpr (enum ExprType type, struct NExpr* left, struct NExpr* right)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = type;
	Result->left = left;
	Result->right = right;

	return Result;
}

struct NExprList* createExprList (struct NExpr* expr)
{
	struct NExprList* Result = (struct NExprList*) malloc(sizeof (struct NExprList));

	Result->first = expr;
	Result->last = expr;

	return Result;
}

struct NExprList* addToExprList (struct NExprList* list, struct NExpr* expr)
{
	list->last->next = expr;
	list->last = expr;

	return list;
}

struct NAssignStmt* createAssignStmt(struct NRefChain* left, struct NExpr* expr)
{
	struct NAssignStmt* Result = (struct NAssignStmt*) malloc(sizeof (struct NAssignStmt));

	Result->left = left;
	Result->expr = expr;

	return Result;
}

struct NRef* createRef(struct NAccess* access, struct NExpr* index)
{
	struct NRef* Result = (struct NRef*) malloc(sizeof (struct NRef));

	Result->access = access;
	Result->index = index;

	return Result;
}

struct NRefChain* createRefChain(struct NRef* ref)
{
	struct NRefChain* Result = (struct NRefChain*) malloc(sizeof (struct NRefChain));

	Result->first = ref;
	Result->last = ref;

	return Result;
}

struct NRefChain* addToRefChain(struct NRefChain* chain, struct NRef* ref)
{
	chain->first->next = ref;
	chain->last = ref;

	return chain;
}

struct NAccess* createAccess(enum AccessType type, char* id, struct NExprList* params)
{
	struct NAccess* Result = (struct NAccess*) malloc(sizeof (struct NAccess));

	Result->type = type;
	Result->id = createId(id);
	Result->params = params;

	return Result;
}

struct NId* createId(char* id)
{
	struct NId* Result = (struct NId*) malloc(sizeof (struct NId));

	strcpy(Result->id, id);

	return Result;
}