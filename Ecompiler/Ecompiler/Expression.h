#pragma once
#include "TreeNode.h"

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	/*methods*/
	static Expression* create(struct NExpr* s);

	/*fields*/
	bool isLeftValue;
};