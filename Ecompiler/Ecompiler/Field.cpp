#include "Field.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Field::Field(void)
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

	fd->type = EiffelType::create(node->type);

	if( ! fd->type )
	{
		qDebug("Field does not declared with a type! where: Field::create()");
		delete fd;
		return false;
	}

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
ByteCode Field::to_ByteCode(ByteCode & bc) {
	return bc;
}