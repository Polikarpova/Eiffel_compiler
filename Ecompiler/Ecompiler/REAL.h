#pragma once
#include "RTLMetaClass.h"

class REAL : public RTLMetaClass, public EiffelType
{

public:

	REAL(void);
	~REAL(void);

	QString descriptor() {return QString("D");}
	QString toReadableString() const {return "REAL";};

};