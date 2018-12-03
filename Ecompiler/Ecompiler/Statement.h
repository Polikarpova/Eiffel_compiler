#pragma once
#include "TreeNode.h"

class Statement : public TreeNode
{

public:

	Statement(void);
	~Statement(void);

	static Statement* create(struct NStmt* s);
};

