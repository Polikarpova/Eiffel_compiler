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

	/* ����������������
	QMap<short int, Field*> fields;		//������� ����� {���-��������� UTF8 -> ����}
	QMap<short int, Method*> methods;	//������� ������� {���-��������� UTF8 -> �����}
	*/
};