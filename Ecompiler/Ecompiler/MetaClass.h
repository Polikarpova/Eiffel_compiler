#pragma once
#include <qlist.h>
#include <qmap.h>
#include "JvmConstant.h"
#include "Field.h"
#include "Method.h"
#include "tree_structs.h"

typedef char byte;

class EiffelProgram;

class MetaClass {

public:

	MetaClass() {};
	~MetaClass() {};

	EiffelProgram* program;

	/*methods*/
	//void doSemantic();
	byte* toByteCode();
	static MetaClass* create(struct NClass* s);

	/*fields*/
	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<short int, Field*> fields;		//таблица полей {имя-константа UTF8 -> поле}
	QMap<short int, Method*> methods;	//таблица методов {имя-константа UTF8 -> метод}

	/*getters*/
	QString name() { return * constantTable.get(name_constN).value.utf8; };

	/*functions*/
	static MetaClass* create(EiffelProgram* program, struct NClass* class_node);

};