#pragma once
#include "RTLMetaClass.h"

class EiffelANY : public RTLMetaClass
{

public:
	
	EiffelANY(void) {
		this->isAbstract = true;
	}
	EiffelANY(EiffelProgram* program) 
		: RTLMetaClass(program, QString("ANY")) {
		this->isAbstract = true;
	}
	~EiffelANY(void);


};