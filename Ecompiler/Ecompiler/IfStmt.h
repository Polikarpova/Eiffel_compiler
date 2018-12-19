#pragma once
#include "Statement.h"
#include "MethodCall.h"

class IfStmt : public Statement
{
public:
	IfStmt(void);
	~IfStmt(void);

	/*fields*/
	MethodCall* generalMethodCall;

	/*methods*/
	static IfStmt* create(Method* mtd, struct NIfStmt* expr);

	ByteCode& toByteCode(ByteCode &);
};
