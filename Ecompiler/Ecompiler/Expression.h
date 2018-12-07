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
	
	//перегружается в дочерних классах
	bool isLeftValue() { return false; };

	//возвращает тип возвращаемый выражением
	//2+2 вернет INTEGER
	EiffelType* expressionType();

	/*fields*/
	struct NExpr* tree_node;

	Expression* left;
	Expression* right;

};