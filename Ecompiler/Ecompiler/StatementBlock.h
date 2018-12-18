#pragma once
#include "Statement.h"
#include <QList>

class Method;

class StatementBlock : public Statement
{

public:

	StatementBlock(void) {this->currentMethod = 0;}
	StatementBlock(Method* mtd) {
		this->currentMethod = mtd;
	}
	~StatementBlock(void) {
		this->body.clear();
	}

	QList<Statement*> body;

	bool createBody(struct NStmtList* List);

	// not supported
	static Statement* create(Method* mtd, struct NStmt* s)
	{
		throw 1;
		return 0;
	}

	virtual ByteCode& toByteCode(ByteCode &bc);
};

