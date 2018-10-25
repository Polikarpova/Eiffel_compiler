#include <stdio.h>
#include "tree_structs.h"

FILE * class2dot(FILE *f, int *min_id, struct NClass* N);


void print2dot(char* filename, struct NClassList* root)
{
	FILE *f = fopen(filename, "w");
	int id = 1;

	fprintf(f, "digraph Eiffel {\n");

	class2dot(f,&id, root->first);



	fprintf(f, "}\n");
	fclose(f);
}

FILE * class2dot(FILE *f, int *min_id, struct NClass* N)
{
	fprintf(f, "%d [label='%s'] \n", *min_id++, N->className );

	return f;
}