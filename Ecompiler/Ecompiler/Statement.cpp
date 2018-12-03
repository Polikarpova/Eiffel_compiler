#include "Statement.h"


Statement::Statement(void)
{
}


Statement::~Statement(void)
{
}

Statement* Statement::create(struct NStmt* s) {

	return new Statement();
}