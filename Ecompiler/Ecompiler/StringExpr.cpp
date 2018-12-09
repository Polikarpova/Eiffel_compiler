#include "StringExpr.h"


StringExpr::StringExpr(void)
{
}


StringExpr::~StringExpr(void)
{
}

/*static*/ StringExpr* StringExpr::create(Method* mtd, struct NExpr* expr) {
	
	StringExpr* se = new StringExpr();

	se->currentMethod = mtd;

	se->tree_node = expr;
	//se->constTableN = ...;
	se->string = QString(expr->value.String);

	return se;
}
