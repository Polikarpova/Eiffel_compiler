#pragma once
#include "MethodCall.h"
#include "StatementBlock.h"

class IfStmt : public Statement
{
public:
	IfStmt(void);
	~IfStmt(void);

	/*fields*/
	MethodCall* generalMethodCall;

	//ThenList* thenPartList;
	
	Expression* condition;
	StatementBlock* ifBody;

	//оба пустые -> просто if
	//есть только elseBody -> if-else
	//есть только elseif -> if-elseif-else (else в самой глубине см. преобразование ifStmt)
	IfStmt* elseif;
	StatementBlock* elseBody;

	/*methods*/
	static IfStmt* create(Method* mtd, struct NIfStmt* stmt);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
