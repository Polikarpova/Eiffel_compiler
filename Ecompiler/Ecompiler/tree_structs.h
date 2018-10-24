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

/* ID - идентификатор */
struct NId
{
	char* id;
	struct NId* next;
};	
struct NIdList
{
	struct NId* first;
	struct NId* last;
};	

enum ExprType {IntE, RealE, CharE, StringE, BoolE, AccessE, RefE, NotE, UPlusE, UMinusE, PowerE, MulE, DivE, PlusE, MinusE, EqualsE, NotEqualE, LessE, GreaterE, LessOrEqualE, GreaterOrEqualE, AndE, AndThenE, OrE, OrElseE, XORE, ImpliesE, ResultE, CurrentE, PrecursorE, CreateE};

/* Expr - выражение */
struct NExpr
{
	enum ExprType type;
	union {
		int Int;
		double Real;
		char Char;
		char* String;
		bool Bool;
		
		struct NRef* ref;
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

/* Access - доступ на чтение/запись/вызов к переменной/атрибуту(полю либо методу) */
struct NAccess
{
	enum yytokentype type; /* допустимо ID, RESULT, CURRENT (см. объявления bison) */
	struct NId* id;	 /* идентификатор */
	struct NExprList* params; /* NULL если отсутствуют (NULL обязательно с RESULT, CURRENT) */
};

/* Ref - обращение к атрибуту или элементу массива */
struct NRef
{
	struct NAccess* access;
	/* Subscript - доступ к элементу массива на чтение/запись */
	struct NExpr* index; /* выражение для индекса (uint). NULL если отсутствует */
	
	struct NRef* next;
};	

/* цепочка обращений через точку */
struct NRefChain
{
	struct NRef* first;
	struct NRef* last;
};

/* Типы операторов */
enum StmtType {CreateSt, AssignSt, RefSt, IfSt, LoopSt};

/* Statement - оператор языка */
struct NStmt
{
	enum StmtType type;
	
	union
	{
		struct NRefChain* ref; // для CreateSt и RefSt
		struct NAssignStmt* assign;
		struct NIfStmt* ifStmt;
		struct NLoopStmt* loopStmt;
	} 
	 body; /* тело (содержимое) оператора */
	
	struct NStmt* next;
};
struct NStmtList
{
	struct NStmt* first;
	struct NStmt* last;
};

enum ValType {ClassV, ArrayV, IntegerV, RealV, CharacterV, StringV, BooleanV};

struct NType
{
	enum Type type;
	char* className;
	struct NType* itemType;
};
 
struct NAssignStmt
{
	struct NRef* left;
	struct NExpr* expr;
};

/*условное втевление*/
struct NIfStmt
{
	struct NThenPartList* thenPart;
	struct NElsePartPart* elsePart;
};

struct NThenPart
{
	struct NExpr* cond;
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
	struct NExpr* cond;
	struct NStmtList* stmtList;
};

#endif /* TREE_STRUCTS_H */
