#pragma once
#include "tree_structs.h"

/** ќбщий тип, приписанный к узлу выражени€ / сущности.
	Ётот класс знает, как нужно создавать байт-код дл€ типовых конструкций,
	используемых с типами Java.
*/
class EiffelType
{

public:

	EiffelType(void);
	~EiffelType(void);

	/*method*/
	static EiffelType* create(struct NType* type);

	virtual bool isVoid() { return false; }
};

