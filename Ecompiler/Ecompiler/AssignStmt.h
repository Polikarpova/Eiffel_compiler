#pragma once
#include "Statement.h"
#include "Expression.h"

class AssignStmt : public Statement
{
public:
	AssignStmt(void);
	~AssignStmt(void);

	/*fields*/
	Expression* leftValue;

	/*methods*/
	static AssignStmt* create(Method* mtd, struct NAssignStmt* s);
};

