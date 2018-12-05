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
	struct NClass* tree_node;

	bool isAbstract;
	EiffelProgram* program;

	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<QString, Field*> fields;		//таблица полей {имя -> поле}
	QMap<QString, Method*> methods;		//таблица методов {имя -> метод}


	/*getters*/
	QString name() { return * constantTable.get(name_constN).value.utf8; }


	/*methods*/
	//void doSemantic();
	byte* toByteCode();
	
	bool createFeatures();


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);
};