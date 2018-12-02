#pragma once
#include <qlist.h>
#include <qmap.h>
#include "JvmConstant.h"
#include "Field.h"
#include "Method.h"
#include "tree_structs.h"

typedef char byte;

class MetaClass {

public:

	MetaClass() {};
	~MetaClass() {};

	/*methods*/
	void doSemantic();
	byte* toByteCode();
	static MetaClass create(struct NClass* s);

	/*fields*/
	short int name, classConstantNumber;
	ConstantTable constantTable;

	MetaClass* parent;

	QMap<short int, Field*> fields;		//������� ����� {���-��������� UTF8 -> ����}
	QMap<short int, Method*> methods;	//������� ������� {���-��������� UTF8 -> �����}
};