#include "FieldRef.h"

#include "Field.h"

FieldRef::FieldRef(void)
	: Expression()
{
}


FieldRef::~FieldRef(void)
{
}


/*static*/ FieldRef* FieldRef::create(Method* mtd, Field* field, Expression* qualification /*= NULL*/ )
{
	FieldRef* fr = new FieldRef();
	fr->currentMethod = mtd;
	fr->left  = qualification;
	fr->field = field;

	fr->type = field->type;

	// report creation
	qDebug("created FieldRef: %s", field->name.toLocal8Bit().data());

	return fr;
}

