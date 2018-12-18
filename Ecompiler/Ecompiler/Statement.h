#pragma once
#include "TreeNode.h"
#include "EiffelProgram.h"
#include "ByteCode.h"

class Method;

class Statement : public TreeNode
{

public:

	Statement(void);
	~Statement(void);
	Method* currentMethod;

	static Statement* create(Method* mtd, struct NStmt* s);

	virtual ByteCode& toByteCode(ByteCode &bc) {return bc.log("/!\\ stmt -> code not implemented!.."); };
};

