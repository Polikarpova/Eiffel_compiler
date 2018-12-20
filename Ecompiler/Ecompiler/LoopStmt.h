#pragma once
#include "StatementBlock.h"

class LoopStmt : public Statement
{
public:
	LoopStmt(void);
	~LoopStmt(void);

	/*fields*/

	/*methods*/
	static LoopStmt* create(Method* mtd, struct NLoopStmt* stmt);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
