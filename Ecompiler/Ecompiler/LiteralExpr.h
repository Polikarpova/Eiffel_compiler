#pragma once
#include "Expression.h"
#include <qstring.h>

class LiteralExpr : public Expression
{

public:
	LiteralExpr(void);
	~LiteralExpr(void);


	/*fields*/
	short int constTableN;
	QString string;

	/*methods*/
	static LiteralExpr* create(struct NExpr* expr);
};
