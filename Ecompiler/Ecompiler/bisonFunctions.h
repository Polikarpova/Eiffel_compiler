#ifndef BISON_FUNCTIONS_H
#define BISON_FUNCTIONS_H

#include <tree_structs.h>
#include <stdlib.h>
#include <string>


struct NExpr* createIntConstExpr (int token);
struct NExpr* createRealConstExpr (double token);
struct NExpr* createCharConstExpr (char token);
struct NExpr* createStringConstExpr (char* token);
struct NExpr* createBoolConstExpr (bool token);
struct NExpr* createRefExpr (struct NRefChain* ref);
struct NExpr* createExpr (enum ExprType type, struct NExpr* left, struct NExpr* right);
struct NExprList* createExprList (struct NExpr* expr);
struct NExprList* addToExprList (struct NExprList* list, struct NExpr* expr);
struct NAssignStmt* createAssignStmt(struct NRefChain* left, struct NExpr* expr);
struct NRef* createRef(struct NAccess* access, struct NExpr* index);
struct NRefChain* createRefChain(struct NRef* ref);
struct NRefChain* addToRefChain(struct NRefChain* chain, struct NRef* ref);
struct NAccess* createAccess(enum AccessType type, char* id, struct NExprList* params);
struct NId* createId(char* id);
struct NIdList* createIdList(struct NId* id);
struct NIdList* addToIdList(struct NIdList* list, struct NId* id);
/*ветвление*/
struct NIfStmt* createIfStmt (struct NThenPartList* thenPartList, struct NElsePart* elsePart);
struct NThenPartList* createThenPartList(struct NThenPart* thenPart);
struct NThenPartList* addToThenPartList(struct NThenPartList* list, struct NThenPart* thenPart);
struct NThenPart* createThenPart(struct NExpr* cond, struct NStmtList* stmtList);
struct NElsePart* createElsePart(struct NStmtList* stmtList);
/*цикл*/
struct NLoopStmt* createFromLoop(struct NStmtList* stmtListOpt, struct NExpr* cond, struct NStmtList* stmtList);
// =================== //
struct NNameAndType* createNameAndType(char* name, struct NType* type);
struct NNameAndTypeList* createNameAndTypeList(struct NNameAndType* elem);
struct NNameAndTypeList* addToNameAndTypeList(struct NNameAndTypeList* list, struct NNameAndType* elem);
struct NNameAndTypeList* joinNameAndTypeLists(struct NNameAndTypeList* list1, struct NNameAndTypeList* list2);
struct NNameAndTypeList* convertIdListToNameAndTypeList(struct NIdList* idList, struct NType* type);
struct NType* createType(enum ValType type, char* className =0 , struct NType* itemType =0 );
struct NStmt* createStmt(enum StmtType type, void* body);
struct NStmtList* createStmtList(struct NStmt* elem);
struct NStmtList* addToStmtList(struct NStmtList* list, struct NStmt* elem);
// ======== features ======== //
struct NFeature* createFeature(char* name, struct NNameAndTypeList* params, struct NType* type, struct NNameAndTypeList* localVars =0, struct NStmtList* routineBody =0);
struct NFeatureList* createFeatureList(struct NFeature* elem);
struct NFeatureList* addToFeatureList(struct NFeatureList* list, struct NFeature* elem);
struct NFeature* createAttributesFrom(char* name, struct NType* type);
struct NFeatureList* joinFeatureLists(struct NFeatureList* list1, struct NFeatureList* list2);
// ======== clients ======== //
struct NIdList* registerClients(struct NIdList* clients);
















#endif /* BISON_FUNCTIONS_H */
