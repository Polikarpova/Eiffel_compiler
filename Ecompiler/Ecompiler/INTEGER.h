#pragma once
#include "RTLMetaClass.h"

class INTEGER : public RTLMetaClass, public EiffelType
{

public:

	INTEGER(void);
	INTEGER(EiffelProgram* program) 
		: RTLMetaClass(program, QString("INTEGER")) {};
	~INTEGER(void);


	bool isInteger() const { return true; }
};

