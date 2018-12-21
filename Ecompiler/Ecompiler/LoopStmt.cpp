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


	int goto_start = 0, body_start = 0, until_start = 0, if_start = 0;

	ByteCode code;

	//загружаем блок стоящий между FROM и UNTIL
	this->fromStmts->toByteCode(code);

	goto_start = code.currentOffset;	//запоминаем место где у нас goto
	code.goto_(0x0000);					//goto на проверку условия

	body_start = code.currentOffset;	//запоминаем начало тела
	this->body->toByteCode(code);		//тело

	//перезаписываем goto
	until_start = code.currentOffset;	//запоминаем начало проверки условия
	int len = +(until_start - goto_start); 
	code.gotoPos(goto_start + 1)
		.u2( len )
		.gotoEnd();
	
	this->condition->toByteCode(code);	//высчитываем условие
	
	if_start = code.currentOffset;
	code.ifne( body_start - if_start );				//ifeq на тело

	return bc.append(code);
}