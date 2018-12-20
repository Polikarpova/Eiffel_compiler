#include "BoolExpr.h"

#include "Method.h"
#include "EiffelClass.h"

BoolExpr::BoolExpr(void)
	: Expression()
{
	this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
}


BoolExpr::~BoolExpr(void)
{
}

/*static*/ BoolExpr* BoolExpr::create(Method* mtd, struct NExpr* expr) {
	
	BoolExpr* be = new BoolExpr();

	be->currentMethod = mtd;
	be->tree_node = expr;
	be->Bool = expr->value.Bool;

	qDebug("created BoolExpr (literal): %s. In method: %s", expr->value.Bool ? "True" : "False", mtd->tree_node->name);

	return be;
}


ByteCode& BoolExpr::toByteCode(ByteCode &bc)
{
	bc.log("bool value");
	
	//загрузить булевую константу
	if ( this->Bool ) {
		bc.iconst_(1);
	} else {
	
		bc.iconst_(0);
	}

	return bc;
}