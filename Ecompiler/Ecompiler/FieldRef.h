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

	/** Задать величину справа от равно.
		Если Выражение не позволяет этого
		сделать, вернётся false.
	*/
	virtual bool setRightValue(Expression* r, bool force = false);

	short int fieldref_constN;

	/*methods*/
	static FieldRef* create(Method* mtd, Field* field, Expression* qualification = NULL );

	ByteCode& toByteCode(ByteCode &);
};