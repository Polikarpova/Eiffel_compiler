#pragma once
#include "RTLMetaClass.h"

class IntegerType : public RTLMetaClass, public EiffelType
{

public:

	IntegerType(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("INTEGER")) , EiffelType() {};
	IntegerType(EiffelProgram* program) 
		: RTLMetaClass(program, QString("INTEGER")) , EiffelType() {};
	~IntegerType(void);

	bool isInteger() const { return true; }

	QString toReadableString() const {return "INTEGER";};

	//ByteCode& toByteCode(ByteCode &bc);

	static IntegerType* singleton;
	static IntegerType* instance() { if(!singleton){singleton=new IntegerType();} return singleton;};
};

