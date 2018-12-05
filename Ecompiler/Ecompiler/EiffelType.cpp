#include "EiffelType.h"

#include "VoidType.h"
#include "EiffelClass.h"

EiffelType::EiffelType(void)
{
}


EiffelType::~EiffelType(void)
{
}

/*static*/ EiffelType* EiffelType::create(struct NType* type) {

	switch(type->type) {
	
		case VoidV:
			return new VoidType();
		case ClassV:
			return 0;
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
	}
}
