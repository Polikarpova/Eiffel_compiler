#pragma once
#include "EiffelType.h"

class MetaArray : public EiffelType
{

public:
	
	MetaArray(void) {};
	~MetaArray(void) {};

	EiffelType * elementType;

};