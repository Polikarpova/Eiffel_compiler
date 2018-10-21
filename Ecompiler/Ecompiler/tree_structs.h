#ifndef SIMPLE_TREE_STRUCTS
#define SIMPLE_TREE_STRUCTS

enum ExprType {Int, Real, Char, String, Bool, Access, Subscript, Prior, Not, UPlus, UMinus, Power, Mul, Div, Plus, Minus, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual, And, AndThen, Or, OrElse, XOR, Implies, Result, Current, Precursor, Create};

struct NExpr
{
	enum ExprType type;
	union {
		int Int,
		double Real,
		char Char,
		char* String,
		bool Bool
	} value;
	struct NExpr* left;
	struct NExpr* right;
	
	struct NExpr* next;
};

struct NExprList
{
	struct NExpr* first;
	struct NExpr* last;
};

//assign_stmt
#endif