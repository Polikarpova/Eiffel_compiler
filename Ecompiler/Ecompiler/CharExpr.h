#pragma once
#include "Expression.h"
#include <qstring.h>

class CharExpr : public Expression
{

public:
	CharExpr(void);
	~CharExpr(void);


	/*fields*/
	short int constTableN;
	char Char;

	/*methods*/
	static CharExpr* create(Method* mtd, struct NExpr* expr);

	ByteCode& toByteCode(ByteCode &);
};
