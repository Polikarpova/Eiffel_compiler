#pragma once
#include "RTLMetaClass.h"

class EiffelCHARACTER : public RTLMetaClass, public EiffelType
{

public:

	EiffelCHARACTER(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("CHARACTER")), EiffelType()
	{
		this->_exprType = this;
	};
	~EiffelCHARACTER(void);

	QString descriptor() {return QString("C");}
	QString toReadableString() const {return "CHARACTER";};

};