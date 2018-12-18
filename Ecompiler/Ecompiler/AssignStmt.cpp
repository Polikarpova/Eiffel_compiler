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

	if ( !left->setRightValue(expr) ) {
	
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Target of assignment is not writable"),
			s->loc.first_line);
			return NULL;

	} else {
	
		as = new AssignStmt();
		as->leftValue->left;
		as->leftValue->left->right = expr;
	}

	return as;
}
