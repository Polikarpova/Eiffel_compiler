#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

/* ѕрототипы */

struct NId;
struct NIdList;
// enum ExprType;
struct NExpr;
struct NExprList;
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
struct NFeature;
struct NFeatureList;
struct NNameAndType;
struct NNameAndTypeList;
struct NInheritFromClass;
struct NInheritFromClassList;


/* —труктуры */

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
	RefnCallE,
	// IdE,  		// uses {value.Id}
	// CallE, 		// uses {left,value.ExprList}
	PrecursorE, // uses {value.Id | NULL}
	/* Chains */
	// QualificationE, 
	SubscriptE
};

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
		
		// struct NId* Id; 
		char* id;

	} value;
	
	struct NExprList* ExprList;  // дл€ CallE
	
	struct NExpr* left;
	struct NExpr* right;
	
	struct NExpr* next;
};
struct NExprList
{
	struct NExpr* first;
	struct NExpr* last;
};

/* “ипы операторов */
enum StmtType {CreateSt, AssignSt, ExprSt, IfSt, LoopSt};

/* Statement - оператор €зыка */
struct NStmt
{
	enum StmtType type;
	
	union
	{
		struct NExpr* expr; // дл€ CreateSt и ExprSt
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

/*  “ип объ€влений */
struct NType
{
	enum ValType type;
	char* className;	// not NULL for ClassV only
	struct NType* itemType; // not NULL for ArrayV only
};
 

/* ќператор присваивани€ */
struct NAssignStmt
{
	struct NExpr* left; // the ref chain must not end with call
	struct NExpr* expr;
};

/* ”словное ветвление */
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
	// признак пол€: routineBody == NULL
	struct NIdList* clients; // видимость дл€: указанных классов / ANY (или пусто?) / NONE
	
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

/* »м€ и тип: формальные параметры и объ€влени€ локальных переменных */
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
