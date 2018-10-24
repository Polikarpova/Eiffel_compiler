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

struct NExpr* createExpr (enum ExprType type, struct NExpr* left, struct NExpr* right)
{
		struct NExpr* Result = (struct NExpr*) malloc(sizeof (struct NExpr));
		
		Result->type = type;
		Result->left = left;
		Result->right = right;

		return Result;
}