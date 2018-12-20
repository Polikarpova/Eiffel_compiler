#include "EiffelType.h"

#include "RTLMetaClass.h"
#include "VoidType.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

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
	//return this->descriptor() == otherType->descriptor();
}


/*static*/ EiffelType* EiffelType::create(struct NType* type) {

	if( ! type )
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Type does not exist in AST."),
			-1);
		return NULL;
	}

	switch(type->type) {
	
		case VoidV:
			return new VoidType(type);
		case ClassV:
			return EiffelClass::create(type);
		case ArrayV:
			return EiffelArray::create(type);
		case IntegerV:
			return IntegerType::instance();
		case RealV:
			return 0;
		case CharacterV:
			return 0;
		case StringV:
			return (EiffelSTRING*) EiffelProgram::currentProgram->findClass("STRING");
		case BooleanV:
			return (EiffelBOOLEAN*) EiffelProgram::currentProgram->findClass("BOOLEAN");
		default:
			return 0;	//unknown
	}
}
