#pragma once
#include "RTLMetaClass.h"

class INTEGER : public RTLMetaClass, public EiffelType
{

public:

	INTEGER(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("INTEGER")) , EiffelType() {};
	INTEGER(EiffelProgram* program) 
		: RTLMetaClass(program, QString("INTEGER")) , EiffelType() {};
	~INTEGER(void);

	QString toReadableString() const {return "INTEGER";};

	bool isInteger() const { return true; }

	//ByteCode& toByteCode(ByteCode &bc);
};

