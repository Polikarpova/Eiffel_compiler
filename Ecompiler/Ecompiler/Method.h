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
	short int	name_constN,
				nameAndType_constN,
				methodref_constN;
	bool isCreator;
	QString descriptor;
	QSet<QString> clients;
	
	/**
	* ¬озвращаемое значение
	*/
	EiffelType* type;

	/**
	* Current [0], параметры [1..paramCount], локальные переменные метода
	* short int : им€ переменной-UTF8
	* Ќомер п/п хранитс€ в LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	int paramCount;

	Statement* body;

	/*methods*/

	static bool create(MetaClass* mc, struct NFeature* node);
};

