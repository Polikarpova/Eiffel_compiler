#pragma once
#include "feature.h"
#include "EiffelType.h"
#include "LocalVariable.h"
#include "Statement.h"
#include "qmap.h"
#include "qset.h"

#include "MetaClass.h"
#include "Expression.h"

typedef char byte;

class Method : public Feature
{

public:

	Method(void);
	~Method(void);

	byte* toByteCode();

	/*fields*/
	bool isCreator;
	//bool isRedefined;
	
	virtual bool isMethod() { return true; }
	virtual bool isField()  { return false;}

	/**
	* Current [0], параметры [1..paramCount], локальные переменные метода
	* ключ : им€ переменной
	* Ќомер п/п хранитс€ в LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	/**  оличество параметров: 1 (Current) + число формальных параметров */
	int paramCount;

	QList<Statement*> body;

	/*methods*/
	bool createBody();

	static Method* create(MetaClass* mc, struct NFeature* node);

	QString createDescriptor(EiffelType* type);
	QString getTypeDescriptor(EiffelType* type);

	bool checkArguments(QList<Expression*> factParams);
};

