#pragma once
#include "Expression.h"

class OperationExpr : public Expression
{

public:
	OperationExpr(void);
	~OperationExpr(void);

	static OperationExpr* create(Method* mtd, struct NExpr* expr);

	/* �� ������� ��� ������� */
	EiffelType* getReturnType();

private:

	EiffelType* getError( QString operType, QString actualType, QString expectedType );
};
