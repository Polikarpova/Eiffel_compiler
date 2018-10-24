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

struct NAssignStmt* createAssignStmt(char* id, struct NExpr* expr)
{
	struct NAssignStmt* Result = (struct NAssignStmt*) malloc(sizeof (struct NAssignStmt));

	//создаем Access, чтобы передать в Ref
	struct NAccess* access = createAccess(ID, id, 0);

	Result->left = createRef(access, 0); //создаем и инициализирем NRef
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

struct NAccess* createAccess(enum yytokentype type, char* id, struct NExprList* params)
{
	struct NAccess* Result = (struct NAccess*) malloc(sizeof (struct NAccess));

	/**/

	return Result;
}