#pragma once
#include "Statement.h"

class CallStmt :
	public Statement
{
public:
	CallStmt(void);
	~CallStmt(void);

	static CallStmt* create(Method* mtd, struct NExpr* expr);
};

