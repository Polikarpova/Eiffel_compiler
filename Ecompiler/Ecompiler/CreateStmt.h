#pragma once
#include "Statement.h"
#include "MethodCall.h"

/** Создание ссылочного объекта.
	create arr.make(0,4);
	create obj.make
	Этот класс - в большой степени копия класса CallStmt.
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

