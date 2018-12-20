#include "RTLMetaClass.h"
#include "Method.h"


RTLMetaClass::RTLMetaClass(void)
{
}
RTLMetaClass::RTLMetaClass(EiffelProgram* program, const QString& name) {
	this->program = program;
	this->parent = NULL;		// важно! Родитель не задаётся (пока вроде бы это не важно)
	this->isAbstract = false;
	this->_exprType = NULL;
	this->tree_node = NULL;

	this->_name = name;

	// add method: constructor
	Method* mtd;
	// void
	EiffelType *void_type = VoidType::instance();
	mtd = new Method(this, void_type, "<init>");
	//// type of this
	//EiffelType *this_type = this->getType();
	//mtd = new Method(this, this_type, "<init>");
	mtd->isCreator = true;
	this->methods[ mtd->name ] = mtd;
};


RTLMetaClass::~RTLMetaClass(void)
{
}
