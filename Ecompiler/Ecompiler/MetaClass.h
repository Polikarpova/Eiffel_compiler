#pragma once
#include <qlist.h>
#include <qmap.h>

#include "tree_structs.h"

#include "JvmConstant.h"
#include "EiffelProgram.h"

typedef char byte;

class EiffelProgram;
class Feature;
class Method;
class Field;

class MetaClass {

public:

	MetaClass() {};
	MetaClass(EiffelProgram* program, const QString& name);
	~MetaClass() {};


	/*fields*/
	struct NClass* tree_node;

	bool isAbstract; // Истина для ANY, NONE
	EiffelProgram* program;

	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<QString, Field*> fields;		//таблица полей {имя -> поле}
	QMap<QString, Method*> methods;		//таблица методов {имя -> метод}


	/*getters*/
	QString name() { return * constantTable.get(name_constN).value.utf8; }

	/** \return NULL if no class found */
	Field* findField(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no class found */
	Method* findMethod(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no class found */
	Feature* findFeature(const QString& lowerName, bool lookInParents = true);


	/*methods*/
	//void doSemantic();
	byte* toByteCode();
	
	/** Проход 2 */
	bool createFeatures();
	/** Проход 3 */
	bool round3();
	bool createInheritance(struct NInheritFromClass* inheritance);
	/** Проход 4 */
	bool generateCode();


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);
};