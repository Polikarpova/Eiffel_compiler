#include "Field.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Field::Field(void) 
	: Feature()
{
}

Field::~Field(void)
{
}

/*static*/ Field* Field::create(MetaClass* mc, struct NFeature* node) {

	QString name(node->name);
	name = name.toLower();

	bool success = false;
	Field* fd = new Field();
	// add to class
	mc->fields[name] = fd;

	fd->name = name;
	fd->metaClass = mc;

	fd->type = EiffelType::create(node->type);

	if( ! fd->type )
	{
		qDebug("Field does not declared with a type! where: Field::create()");
		delete fd;
		return false;
	}

	fd->initJavaName();

	fd->descriptor = fd->createDescriptor();

	success = true;

	// создать константы в классе: имя и дескриптор
	fd->initConstants();


	// report creation
	qDebug("created Field: %s. Descriptor: %s", node->name, fd->getDescriptor().toLocal8Bit().data());

	return success? fd : NULL;
}

QString Field::createDescriptor() {

	return this->type->descriptor();
}

//Таблица поля -> в ByteCode
ByteCode& Field::to_ByteCode(ByteCode & bc) {
//пишем в ByteCode данные об одном поле
	bc.u2(ACC_PUBLIC | addFlags); //флаги
	bc.u2(name_constN); //имя
	bc.log( QString("Field_name, num CONSTANT_Utf8 =")+bc.CombinedPrint(name_constN, 2) );
	bc.u2(descr_constN); //дескриптор
	bc.log( QString("Field_descriptor, num CONSTANT_Utf8 =")+bc.CombinedPrint(descr_constN, 2) );
	bc.u2(0x0000); //кол-во атрибутов
	return bc;
}