#pragma once
#include "Expression.h"

class OperationExpr : public Expression
{

public:
	OperationExpr(void);
	~OperationExpr(void);

	static OperationExpr* create(Method* mtd, struct NExpr* expr);

	/* не трогать эту функцию */
	EiffelType* getReturnType();

private:

	void getError( QString actualType, QString expectedType );
};
