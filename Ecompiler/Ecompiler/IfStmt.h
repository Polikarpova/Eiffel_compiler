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

	//��� ������ -> ������ if
	//���� ������ elseBody -> if-else
	//���� ������ elseif -> if-elseif-else (else � ����� ������� ��. �������������� ifStmt)
	IfStmt* elseif;
	StatementBlock* elseBody;

	/*methods*/
	static IfStmt* create(Method* mtd, struct NIfStmt* stmt);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
