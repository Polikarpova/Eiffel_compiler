#pragma once
#include "Expression.h"

class LocalVariable;

class LocalVariableRef : public Expression
{

public:
	
	LocalVariableRef(void);
	~LocalVariableRef(void);

	/** Задать величину справа от равно.
		Если Выражение не позволяет этого
		сделать, вернётся false.
	*/
	virtual bool setRightValue(Expression* r);

	LocalVariable* locVar;

	static LocalVariableRef* create(Method* mtd, LocalVariable* locVar);

	ByteCode& toByteCode(ByteCode &);
};
