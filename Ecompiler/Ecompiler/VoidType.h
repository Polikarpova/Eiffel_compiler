#pragma once
#include "EiffelType.h"

class VoidType : public EiffelType
{

public:
	
	VoidType(void);
	VoidType(struct NType* type);
	~VoidType(void);

	/*methods*/

	bool isVoid();
	QString descriptor() {return QString("V");}
};