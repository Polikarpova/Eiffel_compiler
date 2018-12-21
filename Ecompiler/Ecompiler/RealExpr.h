#pragma once
#include "Expression.h"
#include <qstring.h>

class RealExpr : public Expression
{

public:
	RealExpr(void);
	~RealExpr(void);

	/*fields*/
	short int constTableN;
	float Real;

	/*methods*/
	static RealExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
