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

struct NIdList* createIdList(struct NId* id)
{
	struct NIdList* Result = (struct NIdList*) malloc(sizeof (struct NIdList));

	Result->first = id;
	Result->last = id;

	return Result;
}

struct NIdList* addToIdList(struct NIdList* list, struct NId* id)
{
	list->first->next = id;
	list->last = id;

	return list;
}

/*ветвление*/
struct NIfStmt* createIfStmt (struct NThenPartList* thenPartList, struct NElsePart* elsePart)
{
	struct NIfStmt* Result = (struct NIfStmt*) malloc(sizeof (struct NIfStmt));

	Result->thenPart = thenPartList;
	Result->elsePart = elsePart;

	return Result;
}

struct NThenPartList* createThenPartList(struct NThenPart* thenPart)
{
	struct NThenPartList* Result = (struct NThenPartList*) malloc(sizeof (struct NThenPartList));

	Result->first = thenPart;
	Result->last = thenPart;

	return Result;
}

struct NThenPartList* addToThenPartList(struct NThenPartList* list, struct NThenPart* thenPart)
{
	list->first->next = thenPart;
	list->last = thenPart;

	return list;
}

struct NThenPart* createThenPart(struct NExpr* cond, struct NStmtList* stmtList)
{
	struct NThenPart* Result = (struct NThenPart*) malloc(sizeof (struct NThenPart));

	Result->cond = cond;
	Result->stmtList = stmtList;

	return Result;
}

struct NElsePart* createElsePart(struct NStmtList* stmtList)
{
	struct NElsePart* Result = (struct NElsePart*) malloc(sizeof (struct NElsePart));

	Result->stmtList = stmtList;

	return Result;
}

/*цикл*/
struct NLoopStmt* createFromLoop(struct NStmtList* stmtListOpt, struct NExpr* cond, struct NStmtList* stmtList)
{
	struct NLoopStmt* Result = (struct NLoopStmt*) malloc(sizeof (struct NLoopStmt));

	Result->stmtListOpt = stmtListOpt;
	Result->cond = cond;
	Result->stmtList = stmtList;

	return Result;
}