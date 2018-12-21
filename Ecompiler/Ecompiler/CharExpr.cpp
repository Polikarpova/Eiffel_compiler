#include "CharExpr.h"

#include "Method.h"
#include "EiffelClass.h"

CharExpr::CharExpr(void)
	: Expression()
{
	this->constTableN = -1;
	this->type = EiffelProgram::currentProgram->findClass("CHARACTER")->getType();
}


CharExpr::~CharExpr(void)
{
}

/*static*/ CharExpr* CharExpr::create(Method* mtd, struct NExpr* expr) {
	
	CharExpr* ce = new CharExpr();

	ce->currentMethod = mtd;
	ce->tree_node = expr;
	ce->Char = expr->value.Char;

	qDebug("created CharExpr (literal): %c. In method: %s", ce->Char, mtd->tree_node->name);

	return ce;
}


ByteCode& CharExpr::toByteCode(ByteCode &bc)
{
	//загрузить символльную константу
	bc.bipush(this->Char);

	return bc;
}