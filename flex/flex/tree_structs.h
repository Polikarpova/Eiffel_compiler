#ifndef SIMPLE_TREE_STRUCTS
#define SIMPLE_TREE_STRUCTS

struct Expression
{
	enum ExprType type;
	int value;
	struct Expression *left;
	struct Expression *right;
};

struct Class
{
	struct Expression *to_print;
};

struct Program
{
	struct Class_List *classes;
};

struct Class_List
{
	struct Class *clas;
	struct Class_List *next;
};

struct EXAMPLE
{
	struct Class *clas;
};
#endif