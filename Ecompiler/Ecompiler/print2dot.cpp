#include "print2dot.h"

void print2dot(char* filename, struct NClassList* root)
{
	FILE *f = fopen(filename, "w");
	int id = 1;

	fprintf(f, "digraph Eiffel {\n");
	classList2dot(f,&id, root);

	fprintf(f, "}\n");
	fclose(f);
}

void classList2dot(FILE *f, int *min_id, struct NClassList* List)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id), "<ROOT>" );

	// iterate features
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "CLASS" );
		class2dot(f, min_id, i); // !!!  доделать
		if(i == List->last) break;
	}/*
	class2dot(f,min_id, List->first);*/
}

void class2dot(FILE *f, int *min_id, struct NClass* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s\"]; \n", (*min_id), N->className );

	int count = 0;

	// inheritance
	if(N->inheritance)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "INHERIT" );
		int heir_id = *min_id;
		fprintf(f, "%d [label=\"%s\"]; \n", heir_id, "parents" );
		count = 0;
		// iterate nodes
		for(struct NInheritFromClass* i = N->inheritance->first  ;  ; i = i->next, ++count )
		{
			// counting edges
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", heir_id, ++(*min_id), count );
			inheritFromClass2dot(f, min_id, i);
			if(i == N->inheritance->last) break;
		}
	}
	
	// constructors
	if(N->creationList)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "CREATE" );
		int ctors_id = *min_id;
		fprintf(f, "%d [label=\"%s\"]; \n", ctors_id, "constructors" );
		count = 0;
		// iterate constructors
		for(struct NId* i = N->creationList->first  ;  ; i = i->next, ++count )
		{
			// counting edges
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", ctors_id, ++(*min_id), count );
			id2dot(f, min_id, i);
			if(i == N->creationList->last) break;
		}
	}
	
	if(N->featureList)
	{
		// iterate features
		count = 0;
		for(struct NFeature* i = N->featureList->first ;  ; i = i->next, ++count )
		{
			fprintf(f, "%d -> %d [label=\"%d\" style=solid]; \n", self_id, ++(*min_id), count );
			feature2dot(f, min_id, i);
			if(i == N->featureList->last) break;
		}
	}
}

void NType2dot(FILE *f, struct NType* type)
{	
	if(!type)
	{
		fprintf(f, "VOID"); return;
	}
	switch(type->type)
	{
		case VoidV:
			fprintf(f, "VOID"); return;
		case ClassV:
			fprintf(f, type->className); return;
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

void feature2dot(FILE *f, int *min_id, struct NFeature* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"%s:", (*min_id)++, N->name );
	NType2dot(f, N->type);
	fprintf(f, "\"]; \n" );

	// clients
	fprintf(f, "%d -> ", self_id );
	clients2dot(f, N->clients);
	fprintf(f, " [label=\"%s\"]; \n", "clients" );


	// params
	if(N->params)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "" );
		int child_id = *min_id;
		fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", child_id, "params" );
		
		if ( N->params->first && N->params->last)
		{
			int count = 0;
			// iterate nodes
			for(struct NNameAndType* i = N->params->first  ;  ; i = i->next, ++count )
			{
				// counting edges
				fprintf(f, "%d -> %d [label=%d style=solid]; \n", child_id, ++(*min_id), count );
				nameAndType2dot(f, min_id, i);
				if(i == N->params->last) break;
			}
		}
	}

	// routineBody
	if(N->routineBody)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "" );
		NStmtList2dot(f, min_id, N->routineBody);
	}

	// locals
	if(N->localVars && N->localVars->first && N->localVars->last)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "" );
		int child_id = *min_id;
		fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", child_id, "locals" );
		int count = 0;
		// iterate locals
		for(struct NNameAndType* i = N->localVars->first  ;  ; i = i->next, ++count )
		{
			// counting edges
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", child_id, ++(*min_id), count );
			nameAndType2dot(f, min_id, i);
			if(i == N->localVars->last) break;
		}
	}
}

void id2dot(FILE *f, int *min_id, struct NId* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"`%s`\" shape=box]; \n", self_id, N->id );
}

void nameAndType2dot(FILE *f, int *min_id, struct NNameAndType* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"`%s`:", self_id, N->name );
	NType2dot(f, N->type);
	fprintf(f, "\"]; \n" );
}
void clients2dot(FILE *f, struct NIdList* List)
{
	// print `"id,id,id, ... ,id"`
	fprintf(f, "\"{");
	// iterate ids
	bool isFirst = true;
	for(struct NId* i = List->first ;  ; i = i->next )
	{
		if(!isFirst)
		{
			fprintf(f, ",");
		}
		fprintf(f, i->id );
		if(i == List->last) break;
		isFirst = false;
	}
	fprintf(f, "}\"");
}
void NStmtList2dot(FILE *f, int *min_id, struct NStmtList* List)
{
	int self_id = *min_id;
	// node

	fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", self_id, "DO..END" );
		
	if ( List->first && List->last)
	{
		int count = 0;
		// iterate nodes
		for(struct NStmt* i = List->first  ;  ; i = i->next, ++count )
		{
			// counting edges
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", self_id, ++(*min_id), count );
			NStmt2dot(f, min_id, i);
			if(i == List->last) break;
		}
	}
	
}
void inheritFromClass2dot(FILE *f, int *min_id, struct NInheritFromClass* N)
{
	int self_id = *min_id;
	// node
	fprintf(f, "%d [label=\"`%s`\"]; \n", self_id, N->className );
	
	// redefines
	if(N->redefineList)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "redefine" );
		int child_id = *min_id;
		fprintf(f, "%d [label=\"%s\"]; \n", child_id, "redefine" );
		int count = 0;
		// iterate nodes
		for(struct NId* i = N->redefineList->first  ;  ; i = i->next, ++count )
		{
			// counting edges
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", child_id, ++(*min_id), count );
			id2dot(f, min_id, i);
			if(i == N->redefineList->last) break;
		}
	}
}

void NStmt2dot(FILE *f, int *min_id, struct NStmt* N)
{	
	switch(N->type) // enum StmtType {CreateSt, AssignSt, RefSt, IfSt, LoopSt};
	{
		case CreateSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "CreateSt" );
			return;
		case AssignSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "AssignSt" );
			return;
		case RefSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "RefSt" );
			return;
		case IfSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "IfSt" );
			return;
		case LoopSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "LoopSt" );
			return;
	}
}

