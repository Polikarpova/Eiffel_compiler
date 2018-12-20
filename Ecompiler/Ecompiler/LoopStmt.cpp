#include "LoopStmt.h"

LoopStmt::LoopStmt(void)
{
	this->currentMethod = 0;
}

LoopStmt::~LoopStmt(void)
{
}

/*static*/ LoopStmt* LoopStmt::create(Method* mtd, struct NLoopStmt* stmt) {

	LoopStmt* ls = new LoopStmt();
	ls->currentMethod = mtd;

	//проверяем условие
	ls->condition = Expression::create(mtd, stmt->cond);

	if ( !ls->condition ) {
		delete ls;
		return 0;
	} else {
	
		if ( ls->condition->expressionType()->isVoid() ) {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Condition ls not an expression. Procedure %1 does not return a value")
					.arg(ls->condition->tree_node->value.id),
				ls->condition->tree_node->loc.first_line);
			delete ls;
			return 0;
		}
		else if ( ls->condition->expressionType()->toReadableString() != "BOOLEAN" ) {

			EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Condition ls not a BOOLEAN expression. cannot convert type %1 into BOOLEAN.")
						.arg(ls->condition->expressionType()->toReadableString()),
					ls->condition->tree_node->loc.first_line);
			delete ls;	
			return 0;
		}
	}

	ls->fromStmts = new StatementBlock(mtd);
	ls->fromStmts->createBody(stmt->stmtListOpt);

	ls->body = new StatementBlock(mtd);
	ls->body->createBody(stmt->stmtList);

	return ls;
}

/*virtual*/ ByteCode& LoopStmt::toByteCode(ByteCode &bc) {

	return bc.log("/!\\ loopStmt not implemented yet");
}