#pragma once
#include "RTLMetaClass.h"

class EiffelSTRING : public RTLMetaClass
{

public:
	
	EiffelSTRING(void);
	EiffelSTRING(EiffelProgram* program) 
		: RTLMetaClass(program, QString("STRING")) {};
	~EiffelSTRING(void);


};