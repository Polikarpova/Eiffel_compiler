#pragma once
#include <qlist.h>
#include <qmap.h>

#include "tree_structs.h"

#include "JvmConstant.h"
#include "EiffelProgram.h"

typedef char byte;

class EiffelProgram;
class Method;
class Field;

class MetaClass {

public:

	MetaClass() {};
	MetaClass(EiffelProgram* program) {this->program = program;};
	~MetaClass() {};


	/*fields*/
	bool isAbstract;
	EiffelProgram* program;

	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<short int, Field*> fields;		//таблица полей {имя-константа UTF8 -> поле}
	QMap<short int, Method*> methods;	//таблица методов {имя-константа UTF8 -> метод}


	/*getters*/
	QString name() { return * constantTable.get(name_constN).value.utf8; };


	/*methods*/
	//void doSemantic();
	byte* toByteCode();


	/*functions*/
	static bool create(struct NClass* class_node);
	
	bool createFeatures(struct NFeatureList* List);
};