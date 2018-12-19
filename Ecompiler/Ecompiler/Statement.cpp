#include "Statement.h"
#include "CallStmt.h"
#include "CreateStmt.h"
#include "AssignStmt.h"
#include "IfStmt.h"

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
			st = CreateStmt::create(mtd, s->body.expr);
		case AssignSt:
			st = AssignStmt::create(mtd, s->body.assign);
			break;
		case ExprSt: //CallSt
			st = CallStmt::create(mtd, s->body.expr);
			break;
		case IfSt:
			st = IfStmt::create(mtd, s->body.ifStmt);
			break;
		case LoopSt:
			break;
		default:
			break;	//unknown
	}

	return st;
}
