#include "EiffelClass.h"

#include "INTEGER.h"
#include "REAL.h"
#include "CHARACTER.h"
#include "EiffelSTRING.h"
#include "BOOLEAN.h"

EiffelClass::EiffelClass(void)
{
}


EiffelClass::~EiffelClass(void)
{
}

/*static*/ EiffelClass* EiffelClass::create(struct NType* type) {

	EiffelClass* ec = new EiffelClass();

	switch(type->type) {
	
		case IntegerV:
			//ec->metaClass = new INTEGER();
			break;
		case RealV:
			//ec->metaClass = new REAL();
			break;
		case CharacterV:
			break;
		case StringV:
			ec->metaClass = new EiffelSTRING();
			break;
		case BooleanV:
			break;
	}

	return ec;
}