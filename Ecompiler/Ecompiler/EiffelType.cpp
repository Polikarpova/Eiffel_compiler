#include "EiffelType.h"

#include "VoidType.h"
#include "EiffelClass.h"

#include <typeinfo>

EiffelType::EiffelType(void)
{
}


EiffelType::~EiffelType(void)
{
}

/*virtual*/ bool EiffelType::canCastTo(const EiffelType* otherType) const
{
	return (typeid(this) == typeid(otherType));
}


/*static*/ EiffelType* EiffelType::create(struct NType* type) {

	if( ! type )
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Type does not exist"),
			-1);
		return NULL;
	}

	switch(type->type) {
	
		case VoidV:
			return new VoidType(type);
		case ClassV:
			return EiffelClass::create(type);
		case ArrayV:
			return 0;
		case IntegerV:
			return 0;
		case RealV:
			return 0;
		case CharacterV:
			return 0;
		case StringV:
			return EiffelClass::create(type);
		case BooleanV:
			return 0;
		default:
			return 0;	//unknown
	}
}
