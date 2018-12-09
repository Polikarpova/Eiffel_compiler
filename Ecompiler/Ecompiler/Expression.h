#pragma once
#include "TreeNode.h"
#include "EiffelType.h"

class Method;

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	Method* currentMethod;

	/*methods*/
	static Expression* create(Method* mtd, struct NExpr* s);
	
	//������������� � �������� �������
	virtual bool isLeftValue() { return false; };

	//���������� ��� ������������ ����������
	//2+2 ������ INTEGER
	EiffelType* expressionType();

	/*fields*/
	struct NExpr* tree_node;

	Expression* left;
	Expression* right;
	EiffelType* type;	//(?)��� ������������� ��������

};