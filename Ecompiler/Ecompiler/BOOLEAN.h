#pragma once
#include "RTLMetaClass.h"

class BOOLEAN : public RTLMetaClass, public EiffelType
{

public:
	
	BOOLEAN(void);
	~BOOLEAN(void);

	QString descriptor() {return QString("Z");}

};