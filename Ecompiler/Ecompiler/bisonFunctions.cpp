#include "bisonFunctions.h"

// extern struct NClass* currentClass = NULL;
extern struct NIdList* currentFeatureClients;

// запоминание текущего положения
extern YYLTYPE global_loc;

#define SAVELOC { Result->loc = global_loc; }

struct NExpr* createIntConstExpr (int token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
	SAVELOC
	Result->type = IntE;
	Result->value.Int = token;

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createRealConstExpr (double token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
	SAVELOC // продолжить
	Result->type = RealE;
	Result->value.Real = token;

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createCharConstExpr (char token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = CharE;
	Result->value.Char = token;

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createStringConstExpr (char* token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = StringE;
	// Result->value.String=(char *)malloc(strlen(token)+1);
	// strcpy(Result->value.String, token);
	Result->value.String=token; // allocated already

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createBoolConstExpr (bool token)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = BoolE;
	Result->value.Bool = token;

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createRefnCallExpr (struct NExpr* left_opt, char* id, struct NExprList* ExprList)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = RefnCallE;
	Result->value.id = id;

	Result->left = left_opt;
	Result->right = NULL;
	Result->next = NULL;

	Result->ExprList = ExprList;
	return Result;
}

// struct NExpr* createIdExpr (struct NId* Id)
// {
	// struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	// Result->type = IdE;
	// Result->value.Id = Id;

	// Result->left = NULL;
	// Result->right = NULL;
	// Result->next = NULL;
	// return Result;
// }

// struct NExpr* createCallExpr (struct NExpr* left_opt, struct NExprList* ExprList_opt)
// {
	// struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	// Result->type = CallE;
	// Result->ExprList = ExprList_opt;

	// Result->left = left_opt;
	// Result->right = NULL;
	// Result->next = NULL;
	// return Result;
// }

struct NExpr* createPrecursorExpr (char* id_opt, struct NExprList* ExprList_opt)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = PrecursorE;
	Result->value.id = id_opt;
	Result->ExprList = ExprList_opt;

	Result->left = NULL;
	Result->right = NULL;
	Result->next = NULL;
	return Result;
}

struct NExpr* createExpr (enum ExprType type, struct NExpr* left, struct NExpr* right)
{
	struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
	Result->type = type;
	Result->left = left;
	Result->right = right;

	Result->next = NULL;
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

struct NAssignStmt* createAssignStmt(struct NExpr* left, struct NExpr* expr)
{
	struct NAssignStmt* Result = (struct NAssignStmt*) malloc(sizeof (struct NAssignStmt));

	Result->left = left;
	Result->expr = expr;

	return Result;
}

// struct NRef* createRef(struct NRef* qualification, struct NAccess* access, struct NExpr* index)
// {
	// struct NRef* Result = (struct NRef*) malloc(sizeof (struct NRef));

	// Result->qualification = qualification;
	// Result->access = access;
	// Result->index = index;

	// return Result;
// }

// struct NAccess* createAccess(enum AccessType type, char* id, struct NExprList* params)
// {
	// struct NAccess* Result = (struct NAccess*) malloc(sizeof (struct NAccess));

	// Result->type = type;
	// Result->id = (id)? createId(id) : NULL;
	// Result->params = params;

	// return Result;
// }

struct NId* createId(char* id)
{
	struct NId* Result = (struct NId*) malloc(sizeof (struct NId));

	Result->id = id;
	
	Result->next = NULL;
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
	list->last->next = id;
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
	list->last->next = thenPart;
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

		// =================== //
		
#define ALLOCATE_POINTER_AS(varname,type) type * varname = (type *) malloc(sizeof (type));
		
struct NNameAndType* createNameAndType(char* name, struct NType* type)
{
	// struct NNameAndType* Result = (struct NNameAndType*) malloc(sizeof (struct NNameAndType));
	ALLOCATE_POINTER_AS(Result, struct NNameAndType)

	Result->name = name;
	Result->type = type;

	Result->next = NULL;
	return Result;
}
struct NNameAndTypeList* createNameAndTypeList(struct NNameAndType* elem)
{
	ALLOCATE_POINTER_AS(Result, struct NNameAndTypeList)

	Result->first = elem;
	Result->last = elem;

	return Result;
}
struct NNameAndTypeList* addToNameAndTypeList(struct NNameAndTypeList* list, struct NNameAndType* elem)
{
	list->last->next = elem;
	list->last = elem;

	return list;
}

struct NNameAndTypeList* joinNameAndTypeLists(struct NNameAndTypeList* list1, struct NNameAndTypeList* list2)
{
	list1->last->next = list2->first;
	list1->last = list2->last;

	list2->first = list2->last = 0;
	delete list2;
	
	return list1;
}

struct NNameAndTypeList* convertIdListToNameAndTypeList(struct NIdList* idList, struct NType* type)
{
	struct NNameAndTypeList* Result;
	// assume idList contains at least 1 element
	struct NId* prevId, *curId = idList->first;
	Result = createNameAndTypeList(createNameAndType(curId->id,type));
	while(curId != idList->last) // curId - последний обработанный элемент
	{
		prevId = curId;
		curId = prevId->next;
		delete prevId;
		addToNameAndTypeList(Result, createNameAndType(curId->id,type));
	}
	
	delete curId;
	delete idList;

	return Result;
}

struct NType* createType(enum ValType type, char* className/* =0 */, struct NType* itemType/* =0 */)
{
	ALLOCATE_POINTER_AS(Result, struct NType)

	Result->type = type;
	Result->className = className;
	Result->itemType = itemType;

	return Result;
}

struct NStmt* createStmt(enum StmtType type, void* body)
{
	ALLOCATE_POINTER_AS(Result, struct NStmt)

	Result->type = type;
	switch(type)
	{
	case CreateSt:
	case ExprSt:
		Result->body.expr    = (struct NExpr*) body; break;
	case AssignSt:
		Result->body.assign = (struct NAssignStmt*) body; break;
	case IfSt:
		Result->body.ifStmt = (struct NIfStmt* ) body; break;
	case LoopSt:
		Result->body.loopStmt=(struct NLoopStmt*) body; break;
	}

	Result->next = NULL;
	return Result;
}
struct NStmtList* createStmtList(struct NStmt* elem)
{
	if(!elem) // drop error stmt
		return NULL;
	
	ALLOCATE_POINTER_AS(Result, struct NStmtList)

	Result->first = elem;
	Result->last = elem;

	return Result;
}
struct NStmtList* addToStmtList(struct NStmtList* list, struct NStmt* elem)
{
	if(!list) // recover list
		return createStmtList(elem);
	if(elem) // drop error stmt
	{
		list->last->next = elem;
		list->last = elem;
	}
	return list;
}

// ======== features ======== //
struct NFeature* createFeature(char* name, struct NNameAndTypeList* params, struct NType* type, struct NNameAndTypeList* localVars/* =0 */, struct NStmtList* routineBody/* =0 */)
{
	ALLOCATE_POINTER_AS(Result, struct NFeature)

	Result->clients = currentFeatureClients; /*use global var*/
	
	Result->name = name;
	Result->params = params;
	Result->type = type;
	Result->localVars = localVars;
	Result->routineBody = routineBody;

	Result->next = NULL;
	return Result;
}
struct NFeatureList* createFeatureList(struct NFeature* elem)
{
	ALLOCATE_POINTER_AS(Result, struct NFeatureList)

	Result->first = elem;
	Result->last = elem;

	return Result;
}
struct NFeatureList* addToFeatureList(struct NFeatureList* list, struct NFeature* elem)
{
	list->last->next = elem;
	list->last = elem;

	return list;
}
// like convert for NameAndTypeList
struct NFeatureList* createAttributesFrom(struct NNameAndTypeList* natList)
{
	struct NFeatureList* Result;
	// assume natList contains at least 1 element
	struct NNameAndType* prevNat, *curNat = natList->first;
	// create attribute & place it into list
	Result = createFeatureList(createFeature(curNat->name,0,curNat->type,0,0));
	while(curNat != natList->last) // curNat - последний обработанный элемент
	{
		prevNat = curNat;
		curNat = prevNat->next;
		delete prevNat;
		addToFeatureList(Result, createFeature(curNat->name,0,curNat->type,0,0));
	}
	
	delete curNat;
	delete natList;

	return Result;
}
struct NFeatureList* joinFeatureLists(struct NFeatureList* list1, struct NFeatureList* list2)
{
	list1->last->next = list2->first;
	list1->last = list2->last;

	list2->first = list2->last = 0;
	delete list2;
	
	return list1;
}

// ======== clients ======== //
struct NIdList* registerClients(struct NIdList* clients)
{
	currentFeatureClients = clients;
	return clients;
}
// ======== classes ======== //
struct NClass* createClass(char* className, struct NInheritFromClassList* inheritance, struct NIdList* creationList, struct NFeatureList* featureList)
{
	ALLOCATE_POINTER_AS(Result, struct NClass)
	
	Result->className = className;
	Result->inheritance = inheritance;
	Result->creationList = creationList;
	Result->featureList = featureList;

	Result->next = NULL;
	return Result;
}
struct NClassList* createClassList(struct NClass* elem)
{
	ALLOCATE_POINTER_AS(Result, struct NClassList)

	Result->first = elem;
	Result->last = elem;

	return Result;
}
struct NClassList* addToClassList(struct NClassList* list, struct NClass* elem)
{
	list->last->next = elem;
	list->last = elem;

	return list;
}

// ======== inheritance ======== //
struct NInheritFromClass* createInheritFromClass(char* className, /*struct NIdList* renameList,	struct NIdList* undefineList,*/	struct NIdList* redefineList)
{
	ALLOCATE_POINTER_AS(Result, struct NInheritFromClass)
	
	Result->className = className;
	/*Result->renameList = renameList;
	Result->undefineList = undefineList; */
	Result->redefineList = redefineList;

	Result->next = NULL;
	return Result;
}
struct NInheritFromClassList* createInheritFromClassList(struct NInheritFromClass* elem)
{
	ALLOCATE_POINTER_AS(Result, struct NInheritFromClassList)

	Result->first = elem;
	Result->last = elem;

	return Result;
}
struct NInheritFromClassList* addInheritFromClassList(struct NInheritFromClassList* list, struct NInheritFromClass* elem)
{
	list->last->next = elem;
	list->last = elem;

	return list;
}

