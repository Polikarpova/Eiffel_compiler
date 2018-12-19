#pragma once
#include "StatementBlock.h"
#include "Expression.h"

class Method;

class ThenPart : public Statement
{

public:

	ThenPart(void);
	~ThenPart(void);

	Expression* condition;
	StatementBlock* body;

	static ThenPart* create(Method* mtd, struct NThenPart* s);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
