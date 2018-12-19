#pragma once
#include "MethodCall.h"
#include "StatementBlock.h"
#include "ThenList.h"

class IfStmt : public Statement
{
public:
	IfStmt(void);
	~IfStmt(void);

	/*fields*/
	MethodCall* generalMethodCall;

	ThenList* thenPartList;
	StatementBlock* elseBody;

	/*methods*/
	static IfStmt* create(Method* mtd, struct NIfStmt* stmt);

	virtual ByteCode& toByteCode(ByteCode &bc) {return bc.log("/!\\ ifStmt -> code not create");;};
};
