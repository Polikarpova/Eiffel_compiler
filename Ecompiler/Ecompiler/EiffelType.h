#pragma once
#include "tree_structs.h"
#include "EiffelProgram.h"


/** ќбщий тип, приписанный к узлу выражени€ / сущности.
	Ётот класс знает, как нужно создавать байт-код дл€ типовых конструкций,
	используемых с типами Java.
*/
class EiffelType
{

public:

	EiffelType(void);
	~EiffelType(void);

	/*fields*/
	struct NType* tree_node;

	/*method*/
	static EiffelType* create(struct NType* type);

	virtual bool isVoid() const { return false; }
	virtual bool isReference() const { return false; }
	virtual bool isClass() const { return false; }
	virtual bool isString() const { return false; }
	virtual bool isArray() const { return false; }
	virtual bool isInteger() const { return false; }
	virtual bool isReal() const { return false; }
	virtual bool isBoolean() const { return false; }

	/** ѕроверка на возможность приведени€ к более общему типу.
		Ќапример, выражени€ справа от равно к типу выражени€ слева.
		ѕо умолчанию тип не может быть приведЄн ни к чему, кроме себ€ -- подклассы могут расширить это поведение.
	*/
	virtual bool canCastTo(const EiffelType* otherType) const;

	virtual QString descriptor() {return QString("<!Type!>");}
	
	virtual QString toReadableString() const {return "Child type did not implemented type helper...";};
};

