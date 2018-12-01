#pragma once
#include <qlist.h>
#include <qmap.h>
#include "JvmConstant.h"
#include "Field.h"
#include "Method.h"

typedef char byte;

class MetaClass {

public:

	MetaClass() {};
	~MetaClass() {};

	byte* toByteCode();

	/*fields*/
	short int name, classConstantNumber;
	ConstantTable constantTable;

	MetaClass* parent;

	QMap<short int, Field*> fields;		//таблица полей {имя-константа UTF8 -> поле}
	QMap<short int, Method*> methods;	//таблица методов {имя-константа UTF8 -> метод}
};