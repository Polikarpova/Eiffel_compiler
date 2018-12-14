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

	/*methods*/
	static FieldRef* create(Method* mtd, Field* field, Expression* qualification = NULL );

};