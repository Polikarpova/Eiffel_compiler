#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

/* Прототипы */

struct NClassList;
struct NClass;
struct NClassBody;
//и далее
struct NAccess;
struct NSubscript;
//и далее
struct NLf;
struct NStmtSep;
//и далее
struct NStmt;
struct NStmtList;
struct NType;
struct NTypeMark;
struct NExpr;
struct NExprList;
struct NAssignStmt;
/*условное ветвление*/
struct NIfStmt;
struct NThenPart;
struct NThenPartList;
struct NElsePart;
/*цикл*/
struct NLoopStmt;


/* Структуры */

struct NAccess
{
	
};

struct NSubscript
{
	
};	

enum StmtType {ASSIGN, ACCESS, IF, LOOP};

struct NStmt
{
	enum StmtType type;
	
	struct NAssignStmt* assign;
	
	struct NAccess* access;
	
	struct NIfStmt* ifStmt;
	struct NLoopStmt* loopStmt;
	
	struct NStmt* next;
};

struct NStmtList
{
	struct NStmt* first;
	struct NStmt* last;
};

enum Type {Array, Integer, Real, Character, String, Boolean};

struct NType
{
	enum Type type;
	struct NType* arrayType;
};

struct NTypeMark
{
	struct NType* type;
};

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
	
	struct NAccess* access;
	struct NSubscript* subscript;
	
	struct NExpr* left;
	struct NExpr* right;
	
	struct NExpr* next;
};

struct NExprList
{
	struct NExpr* first;
	struct NExpr* last;
};

struct NAssignStmt
{
	char* id;
	struct NExpr* expr;
	struct NStmtSep* sep;
};

/*условное втевление*/
struct NIfStmt
{
	struct NThenPartList* thenPart;
	struct NElsePartPart* elsePart;
};

struct NThenPart
{
	struct NExpr* expr;
	struct NStmtList* stmtList;
	
	struct NThenPart* next;
};

struct NThenPartList
{
	struct NThenPart* first;
	struct NThenPart* last;
};

struct NElsePart
{
	struct NStmtList* stmtList;
};

/*цикл*/
struct NLoopStmt
{
	struct NStmtList* stmtListOpt;
	struct NExpr* expr;
	struct NStmtList* stmtList;
};

#endif /* TREE_STRUCTS_H */
