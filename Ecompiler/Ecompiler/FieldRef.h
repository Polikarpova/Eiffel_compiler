#pragma once
#include "Expression.h"

class Field;

class FieldRef : public Expression
{

public:
	FieldRef(void);
	~FieldRef(void);

	//* поле, к которому производится доступ
	Field* field;

	/*methods*/
	static FieldRef* create(Method* mtd, Field* field, Expression* qualification = NULL );

};