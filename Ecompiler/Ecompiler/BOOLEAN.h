#pragma once
#include "RTLMetaClass.h"

class EiffelBOOLEAN : public RTLMetaClass, public EiffelType
{

public:
	
	EiffelBOOLEAN(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("BOOLEAN")) {};
	~EiffelBOOLEAN(void);

	QString descriptor() {return QString("Z");}
	QString toReadableString() const {return "BOOLEAN";};

};