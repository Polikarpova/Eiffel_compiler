#pragma once
#include "RTLMetaClass.h"

class EiffelREAL : public RTLMetaClass, public EiffelType
{

public:

	EiffelREAL(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("REAL")) , EiffelType()
	{
		this->_exprType = this;
	};
	EiffelREAL(EiffelProgram* program) 
		: RTLMetaClass(program, QString("REAL")) , EiffelType()
	{
		this->_exprType = this;
	};

	~EiffelREAL(void);

	virtual bool isReal() const { return true; }

	virtual bool canCastTo(const EiffelType* otherType) const;

	QString descriptor() {return QString("D");}
	QString toReadableString() const {return "REAL";};

	static EiffelREAL* singleton;
	static EiffelREAL* instance() { if(!singleton){singleton=new EiffelREAL();} return singleton;};
};