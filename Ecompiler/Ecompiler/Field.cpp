#include "Field.h"


Field::Field(void)
{
}


Field::~Field(void)
{
}

/*static*/ Field* Field::create(MetaClass* mc, struct NFeature* node) {

	bool success = false;
	Field* fd = NULL;

	return success? fd : NULL;
}

QString Field::createDescriptor() {

	return QString("");
}
