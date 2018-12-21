#pragma once
#include "Expression.h"

class ArrayElemRef : public Expression
{

public:
	ArrayElemRef(void);
	~ArrayElemRef(void);

	Expression* indexExpr;
	//short int fieldref_constN;


	/** ������ �������� ������ �� �����.
		���� ��������� �� ��������� �����
		�������, ������� false.
	*/
	virtual bool setRightValue(Expression* r, bool force = false);

	/*methods*/
	static ArrayElemRef* create(Method* mtd, struct NExpr* s);
	static ArrayElemRef* create(Method* mtd, Expression* arrayExpr, Expression* indexExpr);

	ByteCode& toByteCode(ByteCode &);
};
