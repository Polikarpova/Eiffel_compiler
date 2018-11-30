#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

/* ��������� */

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
/*�������� ���������*/
struct NIfStmt;
struct NThenPart;
struct NThenPartList;
struct NElsePart;
/*����*/
struct NLoopStmt;
/*�����*/
struct NClass;
struct NClassList;
struct NFeature;
struct NFeatureList;
struct NNameAndType;
struct NNameAndTypeList;
struct NInheritFromClass;
struct NInheritFromClassList;


/* ��������� */

/* ID - ������������� */
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

/* Expr - ��������� */
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
	
	struct NExprList* ExprList;  // ��� CallE
	
	struct NExpr* left;
	struct NExpr* right;
	
	struct NExpr* next;
};
struct NExprList
{
	struct NExpr* first;
	struct NExpr* last;
};

/* ���� ���������� */
enum StmtType {CreateSt, AssignSt, ExprSt, IfSt, LoopSt};

/* Statement - �������� ����� */
struct NStmt
{
	enum StmtType type;
	
	union
	{
		struct NExpr* expr; // ��� CreateSt � ExprSt
		struct NAssignStmt* assign;
		struct NIfStmt* ifStmt;
		struct NLoopStmt* loopStmt;
	} 
	 body; /* ���� (����������) ��������� */
	
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

/*  ��� ���������� */
struct NType
{
	enum ValType type;
	char* className;	// not NULL for ClassV only
	struct NType* itemType; // not NULL for ArrayV only
};
 

/* �������� ������������ */
struct NAssignStmt
{
	struct NExpr* left; // the ref chain must not end with call
	struct NExpr* expr;
};

/* �������� ��������� */
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

/*����*/
struct NLoopStmt
{
	struct NStmtList* stmtListOpt;
	struct NExpr* cond;
	struct NStmtList* stmtList;
};

/*�����*/
struct NClass
{
	char* className;
	struct NInheritFromClassList* inheritance; // NULL ���� �����������
	struct NIdList* creationList; // NULL ���� �����������
	struct NFeatureList* featureList; // NULL ���� �����������
	
	struct NClass* next;
};
struct NClassList
{
	struct NClass* first;
	struct NClass* last;
};

struct NFeature
{
	// ������� ����: routineBody == NULL
	struct NIdList* clients; // ��������� ���: ��������� ������� / ANY (��� �����?) / NONE
	
	char* name;
	struct NNameAndTypeList* params; // NULL ���� �����������
	struct NType* type; // attribute type or return type (can be VoidV for return type)
	struct NNameAndTypeList* localVars; // NULL ���� �����������
	struct NStmtList* routineBody; // NULL ���� �� �����
	
	struct NFeature* next;
};
struct NFeatureList
{
	struct NFeature* first;
	struct NFeature* last;
};

/* ��� � ���: ���������� ��������� � ���������� ��������� ���������� */
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
	/*struct NIdList* renameList; // NULL ���� �����������
	struct NIdList* undefineList; // NULL ���� ����������� */
	struct NIdList* redefineList; // NULL ���� �����������
	
	struct NInheritFromClass* next;
};
struct NInheritFromClassList
{
	struct NInheritFromClass* first;
	struct NInheritFromClass* last;
};

#endif /* TREE_STRUCTS_H */
