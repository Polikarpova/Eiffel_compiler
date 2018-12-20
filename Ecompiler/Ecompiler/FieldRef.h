#pragma once
#include "Expression.h"

class Field;

class FieldRef : public Expression
{

public:
	FieldRef(void);
	~FieldRef(void);

	//* ����, � �������� ������������ ������
	Field* field;

	/** ������ �������� ������ �� �����.
		���� ��������� �� ��������� �����
		�������, ������� false.
	*/
	virtual bool setRightValue(Expression* r, bool force = false);

	short int fieldref_constN;

	/*methods*/
	static FieldRef* create(Method* mtd, Field* field, Expression* qualification = NULL );

	ByteCode& toByteCode(ByteCode &);
};