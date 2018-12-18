#include "StatementBlock.h"


bool StatementBlock::createBody(struct NStmtList* List)
{
	if(List) {
		for(struct NStmt* i = List->first ; i != NULL ; i = i->next) {
			// add stmt
			Statement* stmt = Statement::create(this->currentMethod, i);
			if(stmt)
				this->body.append(stmt);

			if(i == List->last) break;
		}
	}

	return true;
}


ByteCode& StatementBlock::toByteCode(ByteCode &bc_main)
{
	ByteCode bc;

	// QList<Statement*> body;

	foreach(Statement* stmt, body)
	{
		stmt->toByteCode(bc);
	}

	return bc_main.append(bc);
}
