#include <stdio.h>
#include "tree_structs.h"

FILE * class2dot(FILE *f, int *min_id, struct NClass* N, struct NClass* LastN);
FILE * feature2dot(FILE *f, int *min_id, struct NFeature* N, struct NFeature* LastN);
FILE * NType2dot(FILE *f, struct NType* type);
FILE * id2dot(FILE *f, int *min_id, struct NId* N, struct NId* LastN);