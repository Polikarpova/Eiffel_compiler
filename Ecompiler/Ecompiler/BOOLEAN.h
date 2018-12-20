#pragma once
#include "RTLMetaClass.h"

class EiffelBOOLEAN : public RTLMetaClass, public EiffelType
{

public:
	
	EiffelBOOLEAN(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("BOOLEAN"))
	{
		this->_exprType = this;
	};
	~EiffelBOOLEAN(void);

	virtual bool isBoolean() const { return true; }

	QString descriptor() {return QString("Z");}
	QString toReadableString() const {return "BOOLEAN";};

};