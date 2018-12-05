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
	MetaClass(EiffelProgram* program, const QString& name);
	~MetaClass() {};


	/*fields*/
	struct NClass* tree_node;

	bool isAbstract; // ������ ��� ANY, NONE
	EiffelProgram* program;

	MetaClass* parent;

	short int name_constN, class_constN;
	ConstantTable constantTable;

	QMap<QString, Field*> fields;		//������� ����� {��� -> ����}
	QMap<QString, Method*> methods;		//������� ������� {��� -> �����}


	/*getters*/
	QString name() { return * constantTable.get(name_constN).value.utf8; }


	/*methods*/
	//void doSemantic();
	byte* toByteCode();
	
	/** ������ 2 */
	bool createFeatures();
	/** ������ 3 */
	bool round3();


	/*functions*/
	static MetaClass* create(struct NClass* class_node);
	static bool isNameConflicting(const QString& upperName);
};