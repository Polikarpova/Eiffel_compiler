#pragma once
#include "Statement.h"
#include "MethodCall.h"

/** �������� ���������� �������.
	create arr.make(0,4);
	create obj.make
	���� ����� - � ������� ������� ����� ������ CallStmt.
*/
class CreateStmt : public Statement
{
public:
	CreateStmt(void);
	~CreateStmt(void);

	/*fields*/
	MethodCall* generalMethodCall;


	/*methods*/
	static CreateStmt* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};

