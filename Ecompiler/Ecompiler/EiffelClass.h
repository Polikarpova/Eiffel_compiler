#pragma once
#include "EiffelType.h"
#include "MetaClass.h"

/** Ссылается на один из классов RTL / пользовательских классов,
	будучи приписанным к узлу выражения / сущности
*/
class EiffelClass : public EiffelType
{

public:
	
	EiffelClass(void);
	EiffelClass(MetaClass* metaClass) {
		this->tree_node = NULL;
		this->metaClass = metaClass;
		this->className = this->metaClass->name();
	}
	~EiffelClass(void);

	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};