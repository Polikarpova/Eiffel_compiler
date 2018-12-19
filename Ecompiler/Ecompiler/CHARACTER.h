#pragma once
#include "RTLMetaClass.h"

class CHARACTER : public RTLMetaClass, public EiffelType
{

public:

	CHARACTER(void);
	~CHARACTER(void);

	QString descriptor() {return QString("C");}
	QString toReadableString() const {return "CHARACTER";};

};