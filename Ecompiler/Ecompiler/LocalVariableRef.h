#pragma once
#include "Expression.h"

class LocalVariable;

class LocalVariableRef : public Expression
{

public:
	
	LocalVariableRef(void);
	~LocalVariableRef(void);

	LocalVariable* locVar;

	static LocalVariableRef* create(Method* mtd, LocalVariable* locVar);
	//static LocalVariableRef* createRtlClassRef(Method* mtd, const QString& uncasedName);

};
