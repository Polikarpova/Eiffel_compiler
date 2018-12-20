#pragma once
#include <qlist.h>
#include <qmap.h>
#include <QDir>

#include "tree_structs.h"

#include "JvmConstant.h"
//#include "EiffelProgram.h"

//typedef char byte;

class EiffelProgram;
class EiffelType;
class EiffelClass;
class Feature;
class Method;
class MethodCall;
class Field;

class MetaClass {

public:

	MetaClass() {};
	MetaClass(EiffelProgram* program, const QString& name);
	~MetaClass();


	/*fields*/

	//* простое им€ класса
	QString _name;

	//* can be NULL for RTL classes
	struct NClass* tree_node;

	bool isRTL() { return tree_node == NULL; }

	bool isAbstract; // »стина дл€ ANY, NONE
	EiffelProgram* program;

	//* parent (NULL for class `ANY`)
	MetaClass* parent;

	short int name_constN, class_constN, super_class_constN, code_constN;
	ConstantTable constantTable;
	/** —оздать константы в классе: им€ и класс, родительский класс.
		Ётот метод можно вызывать сколько угодно раз,
		он добавит (если нету) несозданные ранее константы по родительскому классу.
	*/
	void initConstants();

	QMap<QString, Field*> fields;		//таблица полей {им€ -> поле}
	QMap<QString, Method*> methods;		//таблица методов {им€ -> метод}


	/*getters*/
	//virtual const QString& name() { return * constantTable.get(name_constN).value.utf8; }
	virtual const QString& name() { return _name; }

	virtual QString javaPackage() {return QString("eiffel");}
	
	//* ѕолное квалифицированное им€, типа: `java/lang/String`
	virtual QString fullJavaName() {return QString("%1/%2").arg(javaPackage(), name());}

	/* ѕоиск среди членов класса */
	
	/** \return NULL if no field found */
	Field* findField(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no method found */
	Method* findMethod(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no feature found */
	Feature* findFeature(const QString& lowerName, bool lookInParents = true);

	/** \return NULL if no method found */
	Method* findDefaultConstructor();
	MethodCall* parentsCreatorRef;

	//* тип в выражении
	EiffelType* getType();
	//EiffelClass* getType();

	/*methods*/
	
	/** ѕроход 2 */
	bool createFeatures();
	/** ѕроход 3 */
	bool round3();
	bool createInheritance(struct NInheritFromClass* inheritance);
	//* подготовить специальные методы (конструкторы и геттеры)
	bool makeSpecialMethods();
	/** ѕроход 4 */
	bool generateCode(const QDir& code_dir = QDir());


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);

//protected:
	//* тип в выражении
	EiffelType* _exprType;

public:
	ByteCode& fields_to_ByteCode(ByteCode &bc);
	ByteCode& methods_to_ByteCode(ByteCode &bc);

};