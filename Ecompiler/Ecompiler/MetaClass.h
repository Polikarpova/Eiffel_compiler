#pragma once
#include <qlist.h>
#include <qmap.h>
#include "JvmConstant.h"

class MetaClass {

public:

	MetaClass() {};
	~MetaClass() {};

	/*fields*/
	short int name, classConstantNumber;
	ConstantTable constantTable;

	MetaClass* parent;

	/* раскоментировать
	QMap<short int, Field*> fields;		//таблица полей {имя-константа UTF8 -> поле}
	QMap<short int, Method*> methods;	//таблица методов {имя-константа UTF8 -> метод}
	*/
};