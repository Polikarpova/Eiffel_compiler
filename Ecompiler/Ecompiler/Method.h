#pragma once
#include "feature.h"
#include "FeatureClients.h"
#include "EiffelType.h"
#include "LocalVariable.h"
#include "Statement.h"
#include "qmap.h"

typedef char byte;

class Method : public Feature
{

public:

	Method(void);
	~Method(void);

	byte* toByteCode();

	/*fields*/
	short int	name,
				nameAndTypeConstantNumber,
				methodrefConstantNumber;
	bool isCreator;
	FeatureClients* clients;
	
	/**
	* ¬озвращаемое значение
	*/
	EiffelType* type;

	/**
	* Current [0], параметры [1..paramCount], локальные переменные метода
	* short int : им€ переменной-UTF8
	* Ќомер п/п хранитс€ в LocalVariable
	*/
	QMap<short int, LocalVariable*> localVariables;

	int paramCount;

	Statement* body;
};

