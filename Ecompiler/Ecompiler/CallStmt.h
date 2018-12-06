#pragma once
#include "Statement.h"

class CallStmt :
	public Statement
{
public:
	CallStmt(void);
	~CallStmt(void);

	/*fields*/
	short int methodref_constN;
	Method* currentMethod;

	/*methods*/
	static CallStmt* create(Method* mtd, struct NExpr* expr);

	void createMethodRef(Method* callMethod);
};

