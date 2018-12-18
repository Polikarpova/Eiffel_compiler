#include "FieldRef.h"

#include "Field.h"
#include "Method.h"

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

	/*
		FieldRef
			|_______Class
			|			|_______utf8 - имя
			|
			|_______Name&Type
						|_______utf8 - имя
						|
						|_______utf8 - дескриптор поля
	*/

	// report creation
	qDebug("created FieldRef: %s", field->name.toLocal8Bit().data());
	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	//-----------------Class-----------------//
	//имя класса
	jc.type = UTF8_VALUE;
	buffer = fr->field->metaClass->name();
	jc.value.utf8 = & buffer;
	short int class_utf8 = fr->currentMethod->metaClass->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = class_utf8;
	short int class_class = fr->currentMethod->metaClass->constantTable.put(jc);

	//-----------------Name&Type-----------------//
	//имя поля
	jc.type = UTF8_VALUE;
	buffer = fr->field->javaName;
	jc.value.utf8 = &buffer;
	short int field_name_utf8 = fr->currentMethod->metaClass->constantTable.put(jc);
	
	//дескриптор
	jc.type = UTF8_VALUE;
	buffer = fr->field->getDescriptor();
	jc.value.utf8 = &buffer;
	short int field_descriptor_utf8 = fr->currentMethod->metaClass->constantTable.put(jc);

	//Name&Type Constant
	jc.type = NAME_AND_TYPE;
	jc.value.name_and_type[UTF8_NAME] = field_name_utf8;
	jc.value.name_and_type[UTF8_DESCR] = field_descriptor_utf8;
	short int field_name_and_type = fr->currentMethod->metaClass->constantTable.put(jc);

	//-----------------FieldRef-----------------//
	//FieldRef Constant
	jc.type = FIELD_REF;
	jc.value.field_ref[CONST_CLASS] = class_class;
	jc.value.field_ref[CONST_NAMEnTYPE] = field_name_and_type;
	fr->fieldref_constN = fr->currentMethod->metaClass->constantTable.put(jc);

	return fr;
}


ByteCode& FieldRef::toByteCode(ByteCode &bc)
{
	// load a reference to an object ...
	// call qualification as this->left
	if(this->left)
		this->left->toByteCode(bc); // load qualification
	else
		bc.aload_0(); // load Current


	if(this->isLeftValue()) // eiffel code:   left := right
	{
		this->right->toByteCode(bc); // load right value to store in the field
		bc.putfield(this->fieldref_constN);
	}
	else
	{
		bc.getfield(this->fieldref_constN);
	}

	return bc;
}
