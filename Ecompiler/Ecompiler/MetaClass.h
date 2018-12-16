#pragma once
#include <qlist.h>
#include <qmap.h>
#include <QDir>

#include "tree_structs.h"

#include "JvmConstant.h"
//#include "EiffelProgram.h"

//typedef char byte;

class EiffelProgram;
class EiffelClass;
class Feature;
class Method;
class Field;

class MetaClass {

public:

	MetaClass() {};
	MetaClass(EiffelProgram* program, const QString& name);
	~MetaClass();


	/*fields*/
	//* can be NULL for RTL classes
	struct NClass* tree_node;

	bool isRTL() { return tree_node == NULL; }

	bool isAbstract; // Истина для ANY, NONE
	//bool isStatic; // Истина для IO
	EiffelProgram* program;

	//* parent (NULL for class `ANY`)
	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<QString, Field*> fields;		//таблица полей {имя -> поле}
	QMap<QString, Method*> methods;		//таблица методов {имя -> метод}


	/*getters*/
	virtual const QString& name() { return * constantTable.get(name_constN).value.utf8; }

	virtual QString javaPackage() {return QString("eiffel");}
	
	//* Полное квалифицированное имя, типа: `java/lang/String`
	virtual QString fullJavaName() {return QString("%1/%2").arg(javaPackage(), name());}

	/* Поиск среди членов класса */
	
	/** \return NULL if no field found */
	Field* findField(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no method found */
	Method* findMethod(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no feature found */
	Feature* findFeature(const QString& lowerName, bool lookInParents = true);

	//* тип в выражении
	EiffelClass* getType();

	/*methods*/
	
	/** Проход 2 */
	bool createFeatures();
	/** Проход 3 */
	bool round3();
	bool createInheritance(struct NInheritFromClass* inheritance);
	/** Проход 4 */
	bool generateCode(const QDir& code_dir = QDir());


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);

protected:
	//* тип в выражении
	EiffelClass* _exprType;

};