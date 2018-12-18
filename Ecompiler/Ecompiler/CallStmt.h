#pragma once
#include "Statement.h"
#include "MethodCall.h"

class CallStmt : public Statement
{
public:
	CallStmt(void);
	~CallStmt(void);

	/*fields*/
	MethodCall* generalMethodCall;


	/*methods*/
	static CallStmt* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};

