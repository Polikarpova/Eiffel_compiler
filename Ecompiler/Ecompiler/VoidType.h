#pragma once
#include "EiffelType.h"

class VoidType : public EiffelType
{

public:
	
	VoidType(void);
	~VoidType(void);

	/*methods*/

	bool isVoid();
};