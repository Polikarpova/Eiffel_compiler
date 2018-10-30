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

