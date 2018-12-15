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

	/** OVERRIDE
		Проверка на возможность приведения текущего КЛАССА к более общему КЛАССУ.
		Приведение возможно, если otherType - класс, классы одинаковые или текущий тип является наследником otherType.
	*/
	bool canCastTo(const EiffelType* otherType) const;


	/*fields*/
	MetaClass* metaClass;

	const QString& className();
	//* дескриптор класса с полной квалификацией: `Lпакет.класс;`
	QString descriptor();

	/*methods*/
	static EiffelClass* create(struct NType* type);
};