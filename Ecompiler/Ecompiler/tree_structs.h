#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

/* Прототипы */

struct NId;
struct NIdList;
// enum ExprType;
struct NExpr;
struct NExprList;
// struct NAccess;
// struct NRef;
struct NClassList;
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
struct NInheritFromClass;
struct NInheritFromClassList;


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

enum ExprType
{
	/* Terminals */
	IntE, RealE, CharE, StringE, BoolE,
	/* Unary */
	NotE, UPlusE, UMinusE,
	/* Binary */
	PowerE, MulE, DivE, PlusE, MinusE, EqualsE, NotEqualE, LessE, GreaterE, LessOrEqualE, GreaterOrEqualE, AndE, AndThenE, OrE, OrElseE, XORE, ImpliesE,
	/* IDs & calls */
	IdE,  		// uses {value.Id}
	CallE, 		// uses {left,value.ExprList}
	PrecursorE, // uses {value.Id | NULL}
	/* Chains */
	QualificationE, SubscriptE};

/* Expr - выражение */
struct NExpr
{
	enum ExprType type;
	union {
		int Int;
		double Real;
		char Char;
		char* String;
		bool Bool; // boolean
		
		struct NId* Id; 
		struct NExprList* ExprList;  // для CallE

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

// enum AccessType {IdA, ResultA, CurrentA, PrecursorA};

// /* Access - доступ на чтение/запись/вызов к переменной/атрибуту(полю либо методу) */
// struct NAccess
// {
	// enum AccessType type; /* допустимо ID, RESULT, CURRENT, PRECURSOR (см. объявления bison) */
	// struct NId* id;	 /* идентификатор или класс в конструкции PRECURSOR{ <base> } */
	// struct NExprList* params; /* НЕобязательно с PRECURSOR, разрешено с ID. NULL если отсутствуют (NULL обязательно с RESULT, CURRENT) */
// };

// /* Ref - обращение к атрибуту или элементу массива */
// /* Допустимые варианты (полный список):
	// - просто доступ [0,access,0]
	// - квалифицированный доступ [qual,access,0]
	// - доступ к элементу массива [qual,0,index]
// */
// struct NRef
// {
	// struct NRef* qualification; /* выражение слева от точки. NULL если отсутствует */
	// struct NAccess* access; /* выражение справа от точки. NULL если index не NULL */
	// /* Subscript - доступ к элементу массива на чтение/запись */
	// struct NExpr* index; /* выражение для индекса (uint). Требует qualification не NULL. NULL если access не NULL */
// };	

/* Типы операторов */
enum StmtType {CreateSt, AssignSt, ExprSt, IfSt, LoopSt};

/* Statement - оператор языка */
struct NStmt
{
	enum StmtType type;
	
	union
	{
		struct NExpr* expr; // для CreateSt и ExprSt
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

enum ValType
{
	VoidV, ClassV, ArrayV,
	IntegerV, RealV, CharacterV, StringV, BooleanV
};

/*  Тип объявлений */
struct NType
{
	enum ValType type;
	char* className;	// not NULL for ClassV only
	struct NType* itemType; // not NULL for ArrayV only
};
 

/* Оператор присваивания */
struct NAssignStmt
{
	struct NExpr* left; // the ref chain must not end with call
	struct NExpr* expr;
};

/* Условное ветвление */
struct NIfStmt
{
	struct NThenPartList* thenPart;
	struct NElsePart* elsePart;
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

/*класс*/
struct NClass
{
	char* className;
	struct NInheritFromClassList* inheritance; // NULL если отсутствует
	struct NIdList* creationList; // NULL если отсутствует
	struct NFeatureList* featureList; // NULL если отсутствует
	
	struct NClass* next;
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
	struct NNameAndTypeList* params; // NULL если отсутствует
	struct NType* type; // attribute type or return type (can be VoidV for return type)
	struct NNameAndTypeList* localVars; // NULL если отсутствует
	struct NStmtList* routineBody; // NULL если не метод
	
	struct NFeature* next;
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
	struct NNameAndType* next;
};
struct NNameAndTypeList
{
	struct NNameAndType* first;
	struct NNameAndType* last;
};

struct NInheritFromClass
{
	char* className;
	/*struct NIdList* renameList; // NULL если отсутствует
	struct NIdList* undefineList; // NULL если отсутствует */
	struct NIdList* redefineList; // NULL если отсутствует
	
	struct NInheritFromClass* next;
};
struct NInheritFromClassList
{
	struct NInheritFromClass* first;
	struct NInheritFromClass* last;
};

#endif /* TREE_STRUCTS_H */
