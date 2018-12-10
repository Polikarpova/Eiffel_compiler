#include "EiffelClass.h"
#include "MetaClass.h"

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
EiffelClass::EiffelClass(MetaClass* metaClass) {
	this->tree_node = NULL;
	this->metaClass = metaClass;
	this->className = this->metaClass->name();
}


EiffelClass::~EiffelClass(void)
{
}

/*static*/ EiffelClass* EiffelClass::create(struct NType* type) {

	EiffelProgram* program = EiffelProgram::currentProgram;

	EiffelClass* ec = new EiffelClass();
	ec->tree_node = type;

	switch(type->type) {
	
		case ClassV:
			ec->className = QString(type->className);
			ec->metaClass = program->findClass(ec->className);
			if(ec->metaClass == NULL)
			{
				program->logError(
					QString("semantic"), 
					QString("Using undefined class %1 as type")
					.arg(type->className),
					ec->tree_node->loc.first_line);
				delete ec;
				ec = NULL;
			}
		case IntegerV:
			//ec->metaClass = new INTEGER();
			break;
		case RealV:
			//ec->metaClass = new REAL();
			break;
		case CharacterV:
			//можно забыть
			break;
		case StringV:
			ec->metaClass = program->findClass("STRING");
			break;
		case BooleanV:
			break;
	}

	return ec;
}