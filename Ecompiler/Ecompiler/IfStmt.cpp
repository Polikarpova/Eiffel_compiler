#include "IfStmt.h"

IfStmt::IfStmt(void)
{
	this->currentMethod = 0;
	this->generalMethodCall = 0;
	this->condition = 0;
	this->ifBody = 0;
	this->elseif = 0;
	this->elseBody = 0;
}

IfStmt::~IfStmt(void)
{
}

/*static*/ IfStmt* IfStmt::create(Method* mtd, struct NIfStmt* stmt) {

	bool success = true;
	IfStmt* is = new IfStmt();
	is->currentMethod = mtd;

	//проверяем условие
	is->condition = Expression::create(mtd, stmt->thenPart->first->cond);

	if ( !is->condition ) {
		success = 0;
	} else {
	
		if ( is->condition->expressionType()->isVoid() ) {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Condition is not an expression. Procedure %1 does not return a value")
					.arg(is->condition->tree_node->value.id),
				is->condition->tree_node->loc.first_line);
			delete is;
			return 0;
		}
		else if ( is->condition->expressionType()->toReadableString() != "BOOLEAN" ) {

			EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Condition is not a BOOLEAN expression. cannot convert type %1 into BOOLEAN.")
						.arg(is->condition->expressionType()->toReadableString()),
					is->condition->tree_node->loc.first_line);
			delete is;	
			return 0;
		}
	}

	//записываем самый первый then
	is->ifBody = new StatementBlock(mtd);
	is->ifBody->createBody(stmt->thenPart->first->stmtList);
	
	//если это просто if
	if ( stmt->thenPart->first == stmt->thenPart->last && !stmt->elsePart ) {
		//всё готово
	}
	//это простой if-else
	else if ( stmt->thenPart->first == stmt->thenPart->last && stmt->elsePart ) {
		
		is->elseBody = new StatementBlock(mtd);
		is->elseBody->createBody(stmt->elsePart->stmtList);
	}
	//это множественый выбор
	else if ( stmt->thenPart->first != stmt->thenPart->last ) {
	
		struct NThenPartList thenPartList;
		thenPartList.first = stmt->thenPart->first->next;
		thenPartList.last = stmt->thenPart->last;
		thenPartList.loc = stmt->thenPart->loc;

		struct NIfStmt innerStmt;
		innerStmt.loc = stmt->loc;
		innerStmt.thenPart = &thenPartList;
		innerStmt.elsePart = stmt->elsePart;

		//рекурсия на внутренний IfStmt
		is->elseif = IfStmt::create( mtd, &innerStmt);

		if ( ! is->elseif ) {
		
			success = false;
		}
	}

	return success ? is : 0;
}
