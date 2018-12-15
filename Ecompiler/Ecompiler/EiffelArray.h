#pragma once
#include "EiffelType.h"

class EiffelArray : public EiffelType
{

public:
	
	EiffelArray(void) {};
	~EiffelArray(void) {};

	EiffelType * elementType;

	QString descriptor() { return QString("[%1").arg(elementType->descriptor()); }
};