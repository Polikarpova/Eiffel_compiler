#include "IntegerType.h"

/*static*/ IntegerType* IntegerType::singleton = NULL;


IntegerType::~IntegerType(void)
{
}

/*virtual*/ bool IntegerType::canCastTo(const EiffelType* otherType, EiffelType* *convertTo /*= 0*/) const
{
	if(/*convertTo != NULL &&*/ otherType->isReal()) // преобразование к вещественному числу допускается (если можно рапортовать об этом)
	{
		if(convertTo != NULL) {
			*convertTo = EiffelProgram::currentProgram->findClass("REAL")->getType();
		}
		return true;
	}
	else
	{
		// преобразование не требуется
		convertTo = 0;
	}

	return otherType->isInteger();
}
