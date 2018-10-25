#include "print2dot.h"

void print2dot(char* filename, struct NClassList* root)
{
	FILE *f = fopen(filename, "w");
	int id = 1;

	fprintf(f, "digraph Eiffel {\n");
	classList2dot(f,&id, root->first, root->last);

	fprintf(f, "}\n");
	fclose(f);
}

FILE * classList2dot(FILE *f, int *min_id, struct NClass* List)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id)++, "<ROOT>" );

	// iterate features
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), i->type->className );
		feature2dot(f, min_id, i); // !!!  доделать
		if(i == List->last) break;
	}
	class2dot(f,min_id, root->first, root->last);



}
FILE * class2dot(FILE *f, int *min_id, struct NClass* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id)++, N->className );

	fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, *min_id, "creates" );
	id2dot(f, min_id, N->creationList->first, N->creationList->last);
	
	// iterate features
	for(struct NFeature* i = N->featureList->first ;  ; i = i->next )
	{
		fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++*min_id, i->type->className );
		feature2dot(f, min_id, i, N->featureList->last);
		if(i == N->featureList->last) break;
	}
	
	if(N != LastN)
	{
		fprintf(f, "%d -> %d [label=\"%s\" style=dotted]; \n", self_id, ++*min_id, "next>" );
		class2dot(f, min_id, N->next, LastN);
	}
	return f;
}
FILE * NType2dot(FILE *f, struct NType* type);
{
	
	switch(type->type)
	{
		case VoidV:
			fprintf(f, "VOID"); return;
		case ClassV:
			fprintf(f, type->className); return;
		case VoidV:
			fprintf(f, "VOID"); return;
		case ArrayV:
			fprintf(f, "ARRAY[");
			NType2dot(f, type->itemType);
			fprintf(f, "]"); return;
		case IntegerV:
			fprintf(f, "INTEGER"); return;
		case RealV:
			fprintf(f, "REAL"); return;
		case CharacterV:
			fprintf(f, "CHARACTER"); return;
		case StringV:
			fprintf(f, "STRING"); return;
		case BooleanV:
			fprintf(f, "BOOLEAN"); return;
	}
}
FILE * feature2dot(FILE *f, int *min_id, struct NFeature* N, struct NFeature* LastN)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id)++, N->name );

	// fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, *min_id, "creates" );
	// id2dot(f, min_id, N->creationList->first, N->creationList->last);
	
	// if(N != LastN)
	// {
		// fprintf(f, "%d -> %d [label=\"%s\" style=dotted]; \n", self_id, ++*min_id, "next>" );
		// feature2dot(f, min_id, N->next, LastN);
	// }
	return f;
}

FILE * id2dot(FILE *f, int *min_id, struct NId* N, struct NId* LastN)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id)++, N->id );

	if(N != LastN)
	{
		fprintf(f, "%d -> %d [label=\"%s\" style=dotted]; \n", self_id, *min_id, "next>" );
		id2dot(f, min_id, N->next, LastN);
	}
	return f;
}
