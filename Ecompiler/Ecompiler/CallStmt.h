#pragma once
#include "Statement.h"
#include "ValueMethodCall.h"

class CallStmt : public Statement
{
public:
	CallStmt(void);
	~CallStmt(void);

	/*fields*/
	ValueMethodCall* generalMethodCall;


	/*methods*/
	static CallStmt* create(Method* mtd, struct NExpr* expr);
};

