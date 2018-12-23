#pragma once
#include "RTLMetaClass.h"
#include "EiffelClass.h"

class EiffelSTRING : public RTLMetaClass, public EiffelClass 
{

public:
	
	EiffelSTRING(void)
		: RTLMetaClass(EiffelProgram::currentProgram, QString("STRING")) , EiffelClass(this) {};
	EiffelSTRING(EiffelProgram* program) 
		: RTLMetaClass(program, QString("STRING")) , EiffelClass(this) {};
	~EiffelSTRING(void);

	virtual QString javaPackage() {return QString("java/lang");}
	
	//* Полное квалифицированное имя, типа: `java/lang/String`
	virtual QString fullJavaName() {return QString("%1/%2").arg(javaPackage(), "String");}

	virtual bool isReference() const { return true; }
	virtual bool isString() const { return true; }

	//* тип в выражении
	virtual EiffelSTRING* getType()
	{
		return this;	// EiffelSTRING выступает также в роли EiffelClass
	}

	QString toReadableString() const {return "STRING";};
};