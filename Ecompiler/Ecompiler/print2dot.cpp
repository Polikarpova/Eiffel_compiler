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
		fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", heir_id, "parents" );
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
		fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", ctors_id, "constructors" );
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
	fprintf(f, "%d [label=\"%s:", (*min_id), N->name );
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
	fprintf(f, "%d [label=\"`%s`\" shape=box]; \n", self_id, N->className );
	
	// redefines
	if(N->redefineList)
	{
		fprintf(f, "%d -> %d [label=\"%s\"]; \n", self_id, ++(*min_id), "custom" );
		int child_id = *min_id;
		fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", child_id, "redefine" );
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
			NAssignStmt2dot(f, min_id, N->body.assign);
			return;
		case RefSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "RefSt" );
			return;
		case IfSt:
			NIfStmt2dot(f, min_id, N->body.ifStmt);
			return;
		case LoopSt:
			fprintf(f, "%d [label=\"`%s`\"];", *min_id, "LoopSt" );
			return;
	}
}

void NAssignStmt2dot(FILE *f, int *min_id, struct NAssignStmt* N)
{
	int self_id = *min_id;

	fprintf(f, "%d [label=\"`%s`\"];", self_id, "AssignStmt" );

	//NRef
	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "left" );
	fprintf(f, "%d [label=\"`%s`\"];", *min_id, "leftNode" );

	//NExpr
	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "right" );	//присоединяемый узел описывается внутри функции NExpr2dot
	NExpr2dot(f, min_id, N->expr);
}

void NExpr2dot(FILE *f, int *min_id, struct NExpr* N)
{
	int self_id = *min_id;

	char* shape = "egg";

	switch(N->type)
	{
		case IntE:
		case RealE:
		case CharE:
		case StringE:
		case BoolE:
			constantExpr2dot(f, self_id, N, shape);
			return;
		case RefE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", self_id, "напишите функцию NRef :D", shape );
			//функция обработки NRef
			return;
		case NotE:
		case UPlusE:
		case UMinusE:
			unaryExpr2dot(f, self_id, min_id, N, shape);
			return;
		case PowerE:
		case MulE:
		case DivE:
		case PlusE:
		case MinusE:
		case EqualsE:
		case NotEqualE:
		case LessE:
		case GreaterE:
		case LessOrEqualE:
		case GreaterOrEqualE:
		case AndE:
		case AndThenE:
		case OrE:
		case OrElseE:
		case XORE:
		case ImpliesE:
			binaryExpr2dot(f, self_id, min_id, N, shape);
			return;
	}
}

void constantExpr2dot(FILE *f, int id, struct NExpr* N, char* shape)
{
	switch(N->type)
	{
		case IntE:
			fprintf(f, "%d [label=\"%d\" shape=%s];", id, N->value.Int, shape );
			return;
		case RealE:
			fprintf(f, "%d [label=\"%f5\" shape=%s];", id, N->value.Real, shape );
			return;
		case CharE:
			fprintf(f, "%d [label=\"`%c`\" shape=%s];", id, N->value.Char, shape );
			return;
		case StringE:
			fprintf(f, "%d [label=\"''%s''\" shape=%s];", id, N->value.String, shape );
			return;
		case BoolE:
			if ( N->value.Bool )
			{
				fprintf(f, "%d [label=\"%s\" shape=%s];", id, "true", shape );
			}
			else
			{
				fprintf(f, "%d [label=\"%s\" shape=%s];", id, "false", shape );
			}
			return;
		case RefE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", id, "напишите функцию NRef :D", shape );
			//функция обработки NRef
			return;
	}
}

void unaryExpr2dot(FILE *f, int parent_id, int *min_id, struct NExpr* N, char* shape)
{
	//min_id при передаче не инкрементируется, т.е. по сути он равен parent_id

	switch(N->type)
	{
		case NotE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "NOT", shape );
			break;
		case UPlusE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "+", shape );
			break;
		case UMinusE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "-", shape );
			break;
	}

	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", parent_id, ++(*min_id), "left" );
	NExpr2dot(f, min_id, N->left);
}

void binaryExpr2dot(FILE *f, int parent_id, int *min_id, struct NExpr* N, char* shape)
{
	switch(N->type)
	{
		case PowerE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "^", shape );
			break;
		case MulE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "*", shape );
			break;
		case DivE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "/", shape );
			break;
		case PlusE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "+", shape );
			break;
		case MinusE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "-", shape );
			break;
		case EqualsE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "=", shape );
			break;
		case NotEqualE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "/=", shape );
			break;
		case LessE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "<", shape );
			break;
		case GreaterE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, ">", shape );
			break;
		case LessOrEqualE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "<=", shape );
			break;
		case GreaterOrEqualE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, ">=", shape );
			break;
		case AndE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "AND", shape );
			break;
		case AndThenE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "AND THEN", shape );
			break;
		case OrE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "OR", shape );
			break;
		case OrElseE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "OR ELSE", shape );
			break;
		case XORE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "XOR", shape );
			break;		
		case ImpliesE:
			fprintf(f, "%d [label=\"%s\" shape=%s];", parent_id, "IMPLIES", shape );
			break;
	}

	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", parent_id, ++(*min_id), "left" );
	NExpr2dot(f, min_id, N->left);

	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", parent_id, ++(*min_id), "right" );
	NExpr2dot(f, min_id, N->right);
}

void NIfStmt2dot(FILE *f, int *min_id, struct NIfStmt* N)
{
	int self_id = *min_id;
	// node

	fprintf(f, "%d [label=\"`%s`\"];", self_id, "IfStmt" );
		
	//then_part
	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "" );
	NThenPartList2dot(f, min_id, N->thenPart);
	//fprintf(f, "%d [label=\"`%s`\"];", *min_id, "leftNode" );

	//else_part
	if (N->elsePart) {
		fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "" );	//присоединяемый узел описывается внутри функции NExpr2dot
		NElsePart2dot(f, min_id, N->elsePart);
		//NExpr2dot(f, min_id, N->expr);
	}
}

void NThenPartList2dot(FILE *f, int *min_id, struct NThenPartList* N)
{
	int self_id = *min_id;
	// node

	fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", self_id, "THEN_LIST" );
		
	if ( N->first && N->last)
	{
		int count = 0;
		int then_id = 0;
		// iterate nodes
		for(struct NThenPart* i = N->first  ;  ; i = i->next, ++count )
		{
			// then_block
			fprintf(f, "%d -> %d [label=%d style=solid]; \n", self_id, ++(*min_id), count );
			then_id = *min_id;
			fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", then_id, "THEN_BLOCK" );

			//cond
			fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", then_id, ++(*min_id), "cond" );
			NExpr2dot(f, min_id, i->cond);

			//body
			fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", then_id, ++(*min_id), "body" );
			NStmtList2dot(f, min_id, i->stmtList);
			if(i == N->last) 
				break;
		}
	}
}

void NElsePart2dot(FILE *f, int *min_id, struct NElsePart* N)
{
	int self_id = *min_id;
	// node

	fprintf(f, "%d [label=\"%s\" shape=invhouse]; \n", self_id, "ELSE" );

	fprintf(f, "%d -> %d [label=\"%s\" style=solid]; \n", self_id, ++(*min_id), "body" );
	NStmtList2dot(f, min_id, N->stmtList);
}