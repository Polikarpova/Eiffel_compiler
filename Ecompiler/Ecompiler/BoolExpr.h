#pragma once
#include "Expression.h"
#include <qstring.h>

class BoolExpr : public Expression
{

public:
	BoolExpr(void);
	~BoolExpr(void);


	/*fields*/
	short int constTableN;
	bool Bool;

	/*methods*/
	static BoolExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
