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

/*static*/ EiffelClass* EiffelClass::create(struct NType* node) {

	EiffelProgram* program = EiffelProgram::currentProgram;

	MetaClass* mc = 0;

	switch(node->type) {
	
		case ClassV:
			mc = program->findClass( QString(node->className).toUpper() );
			if(mc == NULL)
			{
				program->logError(
					QString("semantic"), 
					QString("Using undefined class %1 as type")
					.arg(node->className),
					node->loc.first_line);
			}
		case IntegerV:
			//mc = new INTEGER();
			break;
		case RealV:
			//mc = new REAL();
			break;
		case CharacterV:
			//можно забыть
			break;
		case StringV:
			mc = program->findClass("STRING");
			break;
		case BooleanV:
			break;
	}

	if( !mc )
		return NULL;

	return mc->getType();
}