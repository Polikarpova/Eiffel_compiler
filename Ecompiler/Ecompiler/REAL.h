#pragma once
#include "RTLMetaClass.h"

class REAL : public RTLMetaClass, public EiffelType
{

public:

	REAL(void);
	~REAL(void);

	virtual bool isReal() const { return true; }

	QString descriptor() {return QString("D");}
	QString toReadableString() const {return "REAL";};

};