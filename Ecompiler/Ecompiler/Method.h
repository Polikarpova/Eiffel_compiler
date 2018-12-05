#pragma once
#include "feature.h"
#include "EiffelType.h"
#include "LocalVariable.h"
#include "Statement.h"
#include "qmap.h"
#include "qset.h"

#include "MetaClass.h"

typedef char byte;

class Method : public Feature
{

public:

	Method(void);
	~Method(void);

	byte* toByteCode();

	/*fields*/
	bool isCreator;
	

	/**
	* Current [0], параметры [1..paramCount], локальные переменные метода
	* short int : имя переменной-UTF8
	* Номер п/п хранится в LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	int paramCount;

	Statement* body;

	/*methods*/

	static bool create(MetaClass* mc, struct NFeature* node);
};

