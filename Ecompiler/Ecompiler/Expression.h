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
	EiffelType* expressionType();

	/*fields*/
	bool isLeftValue;
};