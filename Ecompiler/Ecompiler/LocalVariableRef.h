#pragma once
#include "Expression.h"

class LocalVariable;

class LocalVariableRef : public Expression
{

public:
	
	LocalVariableRef(void);
	~LocalVariableRef(void);

	/** ������ �������� ������ �� �����.
		���� ��������� �� ��������� �����
		�������, ������� false.
	*/
	virtual bool setRightValue(Expression* r);

	LocalVariable* locVar;

	static LocalVariableRef* create(Method* mtd, LocalVariable* locVar);

	ByteCode& toByteCode(ByteCode &);
};
