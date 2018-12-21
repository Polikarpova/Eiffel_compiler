#pragma once
#include "Expression.h"
#include <qstring.h>

class IntExpr : public Expression
{

public:
	IntExpr(void);
	~IntExpr(void);


	/*fields*/
	short int constTableN;
	signed long int Int;

	/*methods*/
	static IntExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
