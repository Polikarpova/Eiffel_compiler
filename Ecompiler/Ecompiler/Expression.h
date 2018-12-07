#pragma once
#include "TreeNode.h"
#include "EiffelType.h"

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	/*methods*/
	static Expression* create(struct NExpr* s);
	
	//������������� � �������� �������
	bool isLeftValue() { return false; };

	//���������� ��� ������������ ����������
	//2+2 ������ INTEGER
	EiffelType* expressionType();

	/*fields*/
	struct NExpr* tree_node;

	Expression* left;
	Expression* right;

};