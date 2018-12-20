#pragma once
#include "StatementBlock.h"
#include "Expression.h"

class LoopStmt : public Statement
{
public:
	LoopStmt(void);
	~LoopStmt(void);

	/*fields*/
	Expression* condition;
	StatementBlock* fromStmts;
	StatementBlock* body;

	/*methods*/
	static LoopStmt* create(Method* mtd, struct NLoopStmt* stmt);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
