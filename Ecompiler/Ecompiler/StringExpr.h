#pragma once
#include "Expression.h"
#include <qstring.h>

class StringExpr : public Expression
{

public:
	StringExpr(void);
	~StringExpr(void);


	/*fields*/
	short int constTableN;
	QString string;

	/*methods*/
	static StringExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
