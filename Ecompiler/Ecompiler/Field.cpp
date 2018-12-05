#include "Field.h"
#include "EiffelClass.h"

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

	QString result = "";
	
	switch(this->type->tree_node->type) {
	
		case VoidV:
			//Выдать ошибку?
			break;
		case ClassV:
			EiffelClass* ec = (EiffelClass*)this->type;
			result += "L" + ec->className + ";";
			break;
		case ArrayV:
			result += "[";
			break;
		case IntegerV:
			result += "I";
			break;
		case RealV:
			result += "D";
			break;
		case CharacterV:
			result += "C";
			break;
		case StringV:
			result += "Ljava/lang/String;";
			break;
		case BooleanV:
			result += "Z";	//true or false
			break;
	}
	
	return result;
}
