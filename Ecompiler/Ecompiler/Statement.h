#pragma once
#include "TreeNode.h"

#include "EiffelProgram.h"

class Method;

class Statement : public TreeNode
{

public:

	Statement(void);
	~Statement(void);
	Method* currentMethod;

	static Statement* create(Method* mtd, struct NStmt* s);
};

