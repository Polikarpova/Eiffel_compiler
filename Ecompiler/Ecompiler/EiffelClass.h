#pragma once
#include "EiffelType.h"
//#include <QString>
class MetaClass;

/** —сылаетс€ на один из классов RTL / пользовательских классов,
	будучи приписанным к узлу выражени€ / сущности
*/
class EiffelClass : public EiffelType
{

public:
	
	EiffelClass(void);
	EiffelClass(MetaClass* metaClass);
	~EiffelClass(void);

	/** OVERRIDE
		ѕроверка на возможность приведени€ к более общему типу.
		Ќапример, выражени€ справа от равно к типу выражени€ слева.
		ѕо умолчанию тип не может быть приведЄн ни к чему, кроме себ€ -- подклассы могут расширить это поведение.
	*/
	bool canCastTo(const EiffelType* otherType) const;


	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};