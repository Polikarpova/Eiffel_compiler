#include "Statement.h"
#include "CallStmt.h"

Statement* createAssignStmt(Method* mtd, struct NAssignStmt* s);

Statement::Statement(void)
{
}


Statement::~Statement(void)
{
}

/*static*/ Statement* Statement::create(Method* mtd, struct NStmt* s) {

	Statement* st = 0;

	switch(s->type) {
	
		case CreateSt:
			break;
		case AssignSt:
			st = createAssignStmt(mtd, s->body.assign);
			break;
		case ExprSt: //CallSt
			st = CallStmt::create(mtd, s->body.expr);
			break;
		case IfSt:
			break;
		case LoopSt:
			break;
		default:
			break;	//unknown
	}

	return st;
}


Statement* createAssignStmt(Method* mtd, struct NAssignStmt* s) {

	Expression* left = Expression::create(mtd, s->left);
	Expression* expr = Expression::create(mtd, s->expr);

	return 0;
}
