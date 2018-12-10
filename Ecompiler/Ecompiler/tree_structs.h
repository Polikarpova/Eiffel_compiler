#ifndef TREE_STRUCTS_H
#define TREE_STRUCTS_H

/* ��������� */

struct NId;
struct NIdList;
struct NExpr;
struct NExprList;
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


struct YYLTYPE; // from
#include "eiffel_bison.tab.h"

#define DECLLOC struct YYLTYPE loc;

/* ��������� */

/* ID - ������������� */
struct NId
{
	DECLLOC
	char* id;
	struct NId* next;
};	
struct NIdList
{
	DECLLOC
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
	// CallE, 		// uses {left,ExprList}
	PrecursorE, // uses {value.Id | NULL}
	/* Chains */
	// QualificationE, 
	SubscriptE
};

/* Expr - ��������� */
struct NExpr
{
	DECLLOC
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
	DECLLOC
	struct NExpr* first;
	struct NExpr* last;
};

/* ���� ���������� */
enum StmtType {CreateSt, AssignSt, ExprSt, IfSt, LoopSt};

/* Statement - �������� ����� */
struct NStmt
{
	DECLLOC
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
	DECLLOC
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
	DECLLOC
	enum ValType type;
	char* className;	// not NULL for ClassV only
	struct NType* itemType; // not NULL for ArrayV only
};
 

/* �������� ������������ */
struct NAssignStmt
{
	DECLLOC
	struct NExpr* left; // the ref chain must not end with call
	struct NExpr* expr;
};

/* �������� ��������� */
struct NIfStmt
{
	DECLLOC
	struct NThenPartList* thenPart;
	struct NElsePart* elsePart;
};

struct NThenPart
{
	DECLLOC
	struct NExpr* cond;
	struct NStmtList* stmtList;
	
	struct NThenPart* next;
};

struct NThenPartList
{
	DECLLOC
	struct NThenPart* first;
	struct NThenPart* last;
};

struct NElsePart
{
	DECLLOC
	struct NStmtList* stmtList;
};

/*����*/
struct NLoopStmt
{
	DECLLOC
	struct NStmtList* stmtListOpt;
	struct NExpr* cond;
	struct NStmtList* stmtList;
};

/*�����*/
struct NClass
{
	DECLLOC
	char* className;
	struct NInheritFromClassList* inheritance; // NULL ���� �����������
	struct NIdList* creationList; // NULL ���� �����������
	struct NFeatureList* featureList; // NULL ���� �����������
	
	struct NClass* next;
};
struct NClassList
{
	DECLLOC
	struct NClass* first;
	struct NClass* last;
};

struct NFeature
{
	DECLLOC
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
	DECLLOC
	struct NFeature* first;
	struct NFeature* last;
};

/* ��� � ���: ���������� ��������� � ���������� ��������� ���������� */
struct NNameAndType
{
	DECLLOC
	char* name;
	struct NType* type;
	struct NNameAndType* next;
};
struct NNameAndTypeList
{
	DECLLOC
	struct NNameAndType* first;
	struct NNameAndType* last;
};

struct NInheritFromClass
{
	DECLLOC
	char* className;
	/*struct NIdList* renameList; // NULL ���� �����������
	struct NIdList* undefineList; // NULL ���� ����������� */
	struct NIdList* redefineList; // NULL ���� �����������
	
	struct NInheritFromClass* next;
};
struct NInheritFromClassList
{
	DECLLOC
	struct NInheritFromClass* first;
	struct NInheritFromClass* last;
};

#endif /* TREE_STRUCTS_H */
