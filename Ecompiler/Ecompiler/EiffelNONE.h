#pragma once
#include "RTLMetaClass.h"

class EiffelNONE : public RTLMetaClass
{

public:
	
	EiffelNONE(void) {
		this->isAbstract = true;
	}
	EiffelNONE(EiffelProgram* program) 
		: RTLMetaClass(program, QString("NONE")) {
		this->isAbstract = true;
	}
	~EiffelNONE(void);


};