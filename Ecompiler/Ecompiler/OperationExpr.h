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

	virtual ByteCode& toByteCode(ByteCode &bc);

private:

	void getError( QString actualType, QString expectedType );

	ByteCode& unaryToByteCode(ByteCode &bc);
	ByteCode& arithmeticToByteCode(ByteCode &bc);
	ByteCode& comparsionToByteCode(ByteCode &bc);
	ByteCode& logicToByteCode(ByteCode &bc);
};
