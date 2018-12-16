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
	//* for RTL classes
	Method(MetaClass* mc, EiffelType* type, const QString& name, QList<LocalVariable> argList = QList<LocalVariable>() );
	~Method(void);

	//byte* toByteCode();

	/*fields*/
	bool isCreator;
	//bool isRedefined;
	
	virtual bool isMethod() { return true; }
	virtual bool isField()  { return false;}

	/**
	* Current [0], ��������� [1..paramCount), ��������� ���������� ������
	* ���� : ��� ����������
	* ����� �/� �������� � LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	/** ���������� ����������: 1 (Current) + ����� ���������� ���������� */
	int paramCount;
	int exactNumberOfArgs() {return this->paramCount - 1;}

	/** ���� ������ (��� ��������� ������ ������������� ����������� ��������) */
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

