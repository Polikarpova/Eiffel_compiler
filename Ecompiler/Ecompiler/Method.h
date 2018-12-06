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
	//bool isRedefined;
	

	/**
	* Current [0], ��������� [1..paramCount], ��������� ���������� ������
	* ���� : ��� ����������
	* ����� �/� �������� � LocalVariable
	*/
	QMap<QString, LocalVariable*> localVariables;

	/** ���������� ����������: 1 (Current) + ����� ���������� ���������� */
	int paramCount;

	QList<Statement*> body;

	/*methods*/
	bool createBody();

	static Method* create(MetaClass* mc, struct NFeature* node);

	QString createDescriptor(EiffelType* type);
	QString getTypeDescriptor(EiffelType* type);
};

