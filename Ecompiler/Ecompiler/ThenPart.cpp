#include "ThenPart.h"
#include "Method.h"

ThenPart::ThenPart(void)
{
	this->currentMethod = 0;
}


ThenPart::~ThenPart(void)
{
}

/*static*/ ThenPart* ThenPart::create(Method* mtd, struct NThenPart* s) {

	bool success = true;

	ThenPart* tp = new ThenPart();

	tp->condition = Expression::create(mtd, s->cond);

	if ( !tp->condition ) {
		success = 0;
	} else {
	
		if ( tp->condition->expressionType()->isVoid() ) {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Condition is not an expression. Procedure %1 does not return a value")
					.arg(tp->condition->tree_node->value.id),
				tp->condition->tree_node->loc.first_line);
			delete tp;
			return 0;
		}
		else if ( tp->condition->expressionType()->toReadableString() != "BOOLEAN" ) {

			EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Condition is not a BOOLEAN expression. cannot convert type %1 into BOOLEAN.")
						.arg(tp->condition->expressionType()->toReadableString()),
					tp->condition->tree_node->loc.first_line);
			delete tp;	
			return 0;
		}
	}

	tp->body = new StatementBlock(mtd);
	tp->body->createBody(s->stmtList);

	return success ? tp : 0;
}

ByteCode& ThenPart::toByteCode(ByteCode &bc)
{
	return bc.log("/!\\ thenPart code not implemented");
}