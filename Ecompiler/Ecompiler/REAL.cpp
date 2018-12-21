#include "REAL.h"

/*static*/ EiffelREAL* EiffelREAL::singleton = NULL;


EiffelREAL::~EiffelREAL(void)
{
}

/*virtual*/ bool EiffelREAL::canCastTo(const EiffelType* otherType) const
{
	return otherType->isReal();
}