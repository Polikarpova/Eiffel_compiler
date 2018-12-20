#pragma once
#include "Expression.h"
#include <qstring.h>

//всегда записывается в таблицу констант
//у неё свой тип
//называется DOUBLE:
// #2 = Double             0.01d

class RealExpr : public Expression
{

public:
	RealExpr(void);
	~RealExpr(void);

	/*fields*/
	short int constTableN;
	double Real;

	/*methods*/
	static RealExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
