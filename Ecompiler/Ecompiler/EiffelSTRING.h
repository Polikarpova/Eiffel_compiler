#pragma once
#include "RTLMetaClass.h"

class EiffelSTRING : public RTLMetaClass, public EiffelType 
{

public:
	
	EiffelSTRING(void);
	EiffelSTRING(EiffelProgram* program) 
		: RTLMetaClass(program, QString("STRING")) {};
	~EiffelSTRING(void);


	QString descriptor() {return QString("Ljava/lang/String;");}
};