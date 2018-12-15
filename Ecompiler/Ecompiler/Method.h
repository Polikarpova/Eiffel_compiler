#pragma once
#include "feature.h"
#include "EiffelType.h"
#include "LocalVariable.h"
#include "StatementBlock.h"
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
	* ключ : имя переменной
	* Номер п/п хранится в LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	/** Количество параметров: 1 (Current) + число формальных параметров */
	int paramCount;
	int exactNumberOfArgs() {return this->paramCount - 1;}

	/** тело метода (при генерации должно заканчиваться инструкцией возврата) */
	StatementBlock body;

	/*methods*/
	bool createBody();
	LocalVariable* findLocalVar(const QString& lowerName);
	LocalVariable* findLocalVar(int n);


	static Method* create(MetaClass* mc, struct NFeature* node);

	QString createDescriptor();
	//QString getTypeDescriptor(EiffelType* type);

	bool checkArguments(const QList<Expression*>& factParams);
};

