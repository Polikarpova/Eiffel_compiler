#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

// typedef char bool
typedef enum { false, true } boolean;

/* Прототипы */

struct NId;
struct NIdList;
// enum ExprType;
struct NExpr;
struct NExprList;
struct NAccess;
struct NClassList;
struct NRef;
struct NRefChain;
// enum StmtType;
struct NStmt;
struct NStmtList;
struct NType;
struct NAssignStmt;
/*условное ветвление*/
struct NIfStmt;
struct NThenPart;
struct NThenPartList;
struct NElsePart;
/*цикл*/
struct NLoopStmt;
/*класс*/
struct NClass;
struct NClassList;
// struct NCreationList;
struct NFeature;
struct NFeatureList;
struct NNameAndType;
struct NNameAndTypeList;

// struct NClassBody;
// struct NTypeMark;


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
		boolean Bool; // boolean
		
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

/*  Тип объявлений */
struct NType
{
	enum Type type;
	char* className;
	struct NType* itemType;
};
 

/* Оператор присваивания */
struct NAssignStmt
{
	struct NRef* left;
	struct NExpr* expr;
};

/* Условное ветвление */
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

struct NLoopStmt
{
	struct NStmtList* stmtListOpt;
	struct NExpr* cond;
	struct NStmtList* stmtList;
};

/*класс*/
struct NClass
{
	char* className;
	struct NIdList* creationList; // NULL если отсутствует
	// // struct NStmtList* clientsList;
	struct NFeatureList* featureList; // NULL если отсутствует
	
};
struct NClassList
{
	struct NClass* first;
	struct NClass* last;
};

struct NFeature
{
	// признак поля: routineBody == NULL
	struct NIdList* clients; // видимость для: указанных классов / ANY (или пусто?) / NONE
	
	char* name;
	struct NType* type; // attribute type or return type (can be NULL for return type)
	struct NNameAndTypeList* params; // NULL если отсутствует
	struct NNameAndTypeList* localVars; // NULL если отсутствует
	struct NStmtList* routineBody; // NULL если не метод
};
struct NFeatureList
{
	struct NFeature* first;
	struct NFeature* last;
};

/* Имя и тип: формальные параметры и объявления локальных переменных */
struct NNameAndType
{
	char* name;
	struct NType* type;
};
struct NNameAndTypeList
{
	struct NNameAndType* first;
	struct NNameAndType* last;
};


#endif /* TREE_STRUCTS_H */
