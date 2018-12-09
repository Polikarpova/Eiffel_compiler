#include "LiteralExpr.h"


LiteralExpr::LiteralExpr(void)
{
}


LiteralExpr::~LiteralExpr(void)
{
}

/*static*/ LiteralExpr* LiteralExpr::create(struct NExpr* expr) {
	
	LiteralExpr* le = new LiteralExpr();

	le->tree_node = expr;
	//le->constTableN = ...;
	le->string = QString(expr->value.String);

	return le;
}
