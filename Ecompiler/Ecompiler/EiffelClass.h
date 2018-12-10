#pragma once
#include "EiffelType.h"
//#include <QString>
class MetaClass;

/** Ссылается на один из классов RTL / пользовательских классов,
	будучи приписанным к узлу выражения / сущности
*/
class EiffelClass : public EiffelType
{

public:
	
	EiffelClass(void);
	EiffelClass(MetaClass* metaClass);
	~EiffelClass(void);

	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};