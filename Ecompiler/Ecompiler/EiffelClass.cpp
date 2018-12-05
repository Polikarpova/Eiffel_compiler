#include "EiffelClass.h"

#include "INTEGER.h"
#include "REAL.h"
#include "CHARACTER.h"
#include "EiffelSTRING.h"
#include "BOOLEAN.h"

EiffelClass::EiffelClass(void)
{
	this->className = "";
	this->metaClass = 0;
}


EiffelClass::~EiffelClass(void)
{
}

/*static*/ EiffelClass* EiffelClass::create(struct NType* type) {

	EiffelClass* ec = new EiffelClass();

	ec->tree_node = type;

	switch(type->type) {
	
		case ClassV:
			//ec->metaClass = //?
			ec->className = QString(type->className);
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