#pragma once
#include "RTLMetaClass.h"

class IntegerType : public RTLMetaClass, public EiffelType
{

public:

	IntegerType(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("INTEGER")) , EiffelType()
	{
		this->_exprType = this;
	};
	IntegerType(EiffelProgram* program) 
		: RTLMetaClass(program, QString("INTEGER")) , EiffelType()
	{
		this->_exprType = this;
	};

	~IntegerType(void);

	bool isInteger() const { return true; }

	virtual bool canCastTo(const EiffelType* otherType, EiffelType* *convertTo = 0) const;

	virtual QString descriptor() {return "I";};
	QString toReadableString() const {return "INTEGER";};

	//ByteCode& toByteCode(ByteCode &bc);

	static IntegerType* singleton;
	static IntegerType* instance() { if(!singleton){singleton=new IntegerType();} return singleton;};
};

