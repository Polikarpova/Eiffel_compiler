#include <stdio.h>
#include "tree_structs.h"

void print2dot(char* filename, struct NClassList* root);
void classList2dot(FILE *f, int *min_id, struct NClassList* List);
void class2dot(FILE *f, int *min_id, struct NClass* N);
void feature2dot(FILE *f, int *min_id, struct NFeature* N);
void NType2dot(FILE *f, struct NType* type);
void id2dot(FILE *f, int *min_id, struct NId* N);
void nameAndType2dot(FILE *f, int *min_id, struct NNameAndType* N);
void clients2dot(FILE *f, struct NIdList* List);
void NStmtList2dot(FILE *f, int *min_id, struct NStmtList* List);
void inheritFromClass2dot(FILE *f, int *min_id, struct NInheritFromClass* N);
void NStmt2dot(FILE *f, int *min_id, struct NStmt* N);
void NAssignStmt2dot(FILE *f, int *min_id, struct NAssignStmt* N);
void NExpr2dot(FILE *f, int *min_id, struct NExpr* N);
void constantExpr2dot(FILE *f, int id, struct NExpr* N, char* shape);
void unaryExpr2dot(FILE *f, int parent_id, int *min_id, struct NExpr* N, char* shape);
void binaryExpr2dot(FILE *f, int parent_id, int *min_id, struct NExpr* N, char* shape);
void NIfStmt2dot(FILE *f, int *min_id, struct NIfStmt* N);
void NThenPartList2dot(FILE *f, int *min_id, struct NThenPartList* N);
void NElsePart2dot(FILE *f, int *min_id, struct NElsePart* N);
void NLoopStmt2dot(FILE *f, int *min_id, struct NLoopStmt* N);
void loopFrom2dot(FILE *f, int *min_id, struct NStmtList* N);
void loopUntil2dot(FILE *f, int *min_id, struct NExpr* N);
void loopBody2dot(FILE *f, int *min_id, struct NStmtList* N);
void call2dot(FILE *f, int *min_id, struct NExpr* N);
// void access2dot(FILE *f, int *min_id, struct NAccess* N);
// void ref2dot(FILE *f, int *min_id, struct NRef* N);

