#pragma once
#include "Expression.h"

class OperationExpr : public Expression
{

public:
	OperationExpr(void);
	~OperationExpr(void);

	static OperationExpr* create(struct NExpr* expr);
};
