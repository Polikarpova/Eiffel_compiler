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

	//* ������� ��� ������
	QString _name;

	//* can be NULL for RTL classes
	struct NClass* tree_node;

	bool isRTL() { return tree_node == NULL; }

	bool isAbstract; // ������ ��� ANY, NONE
	EiffelProgram* program;

	//* parent (NULL for class `ANY`)
	MetaClass* parent;

	short int name_constN, class_constN, super_class_constN, code_constN;
	ConstantTable constantTable;
	/** ������� ��������� � ������: ��� � �����, ������������ �����.
		���� ����� ����� �������� ������� ������ ���,
		�� ������� (���� ����) ����������� ����� ��������� �� ������������� ������.
	*/
	void initConstants();

	QMap<QString, Field*> fields;		//������� ����� {��� -> ����}
	QMap<QString, Method*> methods;		//������� ������� {��� -> �����}


	/*getters*/
	//virtual const QString& name() { return * constantTable.get(name_constN).value.utf8; }
	virtual const QString& name() { return _name; }

	virtual QString javaPackage() {return QString("eiffel");}
	
	//* ������ ����������������� ���, ����: `java/lang/String`
	virtual QString fullJavaName() {return QString("%1/%2").arg(javaPackage(), name());}

	/* ����� ����� ������ ������ */
	
	/** \return NULL if no field found */
	Field* findField(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no method found */
	Method* findMethod(const QString& lowerName, bool lookInParents = true);
	/** \return NULL if no feature found */
	Feature* findFeature(const QString& lowerName, bool lookInParents = true);

	/** \return NULL if no method found */
	Method* findDefaultConstructor();
	MethodCall* parentsCreatorRef;

	//* ��� � ���������
	EiffelType* getType();
	//EiffelClass* getType();

	/*methods*/
	
	/** ������ 2 */
	bool createFeatures();
	/** ������ 3 */
	bool round3();
	bool createInheritance(struct NInheritFromClass* inheritance);
	//* ����������� ����������� ������ (������������ � �������)
	bool makeSpecialMethods();
	/** ������ 4 */
	bool generateCode(const QDir& code_dir = QDir());


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);

//protected:
	//* ��� � ���������
	EiffelType* _exprType;

public:
	ByteCode& fields_to_ByteCode(ByteCode &bc);
	ByteCode& methods_to_ByteCode(ByteCode &bc);

};