#include "Statement.h"
#include "CallStmt.h"
#include "AssignStmt.h"

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
			st = AssignStmt::create(mtd, s->body.assign);
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
