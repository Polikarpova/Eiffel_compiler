#include "StringExpr.h"


StringExpr::StringExpr(void)
{
}


StringExpr::~StringExpr(void)
{
}

/*static*/ StringExpr* StringExpr::create(struct NExpr* expr) {
	
	StringExpr* le = new StringExpr();

	le->tree_node = expr;
	//le->constTableN = ...;
	le->string = QString(expr->value.String);

	return le;
}
