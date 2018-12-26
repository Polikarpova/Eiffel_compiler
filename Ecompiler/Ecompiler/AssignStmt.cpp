#include "AssignStmt.h"

AssignStmt::AssignStmt(void)
{
}

AssignStmt::~AssignStmt(void)
{
}

/*static*/ AssignStmt* AssignStmt::create(Method* mtd, struct NAssignStmt* s) {

	AssignStmt* as = 0;

	Expression* left = Expression::create(mtd, s->left);
	Expression* expr = Expression::create(mtd, s->expr);

	if ( left != NULL && expr != NULL ) {
	
		EiffelType *lType = left->expressionType();
		EiffelType *rType = expr->expressionType();

		EiffelType* convertType = 0;

		if ( ! rType->canCastTo( lType, &convertType ) ) {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Invalid assignment: cannot convert type from `%1` to `%2`.")
					.arg(rType->toReadableString(), lType->toReadableString()),
				s->expr->loc.first_line);
			return NULL;
		}

		// установить узлу преобразование
		if(convertType != 0)
		{
			expr->setConversionTo(convertType);
		}

	} else {
		return NULL;
	}
		
	if( !left->setRightValue(expr) ) {

		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Target of assignment is not writable."),
			s->loc.first_line);
		return NULL;
	}

	as = new AssignStmt();
	as->leftValue = left;

	// report creation
	qDebug("created AssignStmt: %s", QString("`%1` := `%2`.")
					.arg(left->type->toReadableString(), expr->type->toReadableString())
					.toLocal8Bit().data()
					);

	return as;
}

ByteCode& AssignStmt::toByteCode(ByteCode &bc)
{
	// вызвать нижележащий узел: обращение к методу
	return leftValue->toByteCode(bc);
}
