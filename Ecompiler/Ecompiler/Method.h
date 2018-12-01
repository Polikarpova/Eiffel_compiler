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
	* ������������ ��������
	*/
	EiffelType* type;

	/**
	* Current [0], ��������� [1..paramCount], ��������� ���������� ������
	* short int : ��� ����������-UTF8
	* ����� �/� �������� � LocalVariable
	*/
	QMap<short int, LocalVariable*> localVariables;

	int paramCount;

	Statement* body;
};

