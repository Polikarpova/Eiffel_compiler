#pragma once
#include "Expression.h"
#include <QString>

class StringExpr : public Expression
{

public:
	StringExpr(void);
	~StringExpr(void);


	/*fields*/
	short int constTableN;
	QString string;

	/*methods*/
	static StringExpr* create(struct NExpr* expr);
};
