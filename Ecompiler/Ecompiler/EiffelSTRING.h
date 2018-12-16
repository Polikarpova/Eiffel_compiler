#pragma once
#include "RTLMetaClass.h"
#include "EiffelClass.h"

class EiffelSTRING : public RTLMetaClass, public EiffelClass 
{

public:
	
	EiffelSTRING(void);
	EiffelSTRING(EiffelProgram* program) 
		: RTLMetaClass(program, QString("STRING")) {};
	~EiffelSTRING(void);
};