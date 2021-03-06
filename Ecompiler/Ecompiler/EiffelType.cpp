#include "EiffelType.h"

#include "RTLMetaClass.h"
#include "VoidType.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

#include "CHARACTER.h"
#include "REAL.h"

#include <typeinfo>

EiffelType::EiffelType(void)
{
}


EiffelType::~EiffelType(void)
{
}

/*virtual*/ bool EiffelType::canCastTo(const EiffelType* otherType, EiffelType* *convertTo /*= 0*/) const
{
	// преобразование не требуется
	convertTo = 0;

	return 
	   this->isVoid()      == otherType->isVoid()
	&& this->isReference() == otherType->isReference()
	&& this->isClass()     == otherType->isClass()
	&& this->isString()    == otherType->isString()
	&& this->isArray()     == otherType->isArray()
	&& this->isInteger()   == otherType->isInteger()
	&& this->isReal()      == otherType->isReal()
	&& this->isBoolean()   == otherType->isBoolean()
	&& this->isCharacter() == otherType->isCharacter();

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
			return EiffelREAL::instance();
		case CharacterV:
			return (EiffelCHARACTER*) EiffelProgram::currentProgram->findClass("CHARACTER");
		case StringV:
			return (EiffelSTRING*) EiffelProgram::currentProgram->findClass("STRING");
		case BooleanV:
			return (EiffelBOOLEAN*) EiffelProgram::currentProgram->findClass("BOOLEAN");
		default:
			return 0;	//unknown
	}
}
