#include "IfStmt.h"

IfStmt::IfStmt(void)
{
	this->currentMethod = 0;
	this->generalMethodCall = 0;
	this->thenPartList = new ThenList();
	this->elseBody = 0;
}

IfStmt::~IfStmt(void)
{
}

/*static*/ IfStmt* IfStmt::create(Method* mtd, struct NIfStmt* stmt) {

	bool success = true;
	IfStmt* is = new IfStmt();
	is->currentMethod = mtd;
	
	if ( !is->thenPartList->create(is->currentMethod, stmt->thenPart)) {
		
		success = false;
	} else {
		is->elseBody = new StatementBlock(mtd);
		is->elseBody->createBody(stmt->elsePart->stmtList);
	}

	return success ? is : 0;
}
