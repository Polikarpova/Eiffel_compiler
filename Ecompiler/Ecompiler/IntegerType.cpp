#include "IntegerType.h"

/*static*/ IntegerType* IntegerType::singleton = NULL;


IntegerType::~IntegerType(void)
{
}

/*virtual*/ bool IntegerType::canCastTo(const EiffelType* otherType) const
{
	return otherType->isInteger();
}
