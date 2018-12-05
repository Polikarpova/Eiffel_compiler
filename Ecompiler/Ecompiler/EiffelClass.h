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
	~EiffelClass(void);

	/*fields*/
	MetaClass* metaClass;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};