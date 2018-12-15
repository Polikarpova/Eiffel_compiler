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
	fd->descriptor = fd->createDescriptor();

	success = true;

	// report creation
	qDebug("created Field: %s", node->name);

	return success? fd : NULL;
}

QString Field::createDescriptor() {

	QString result = "";
	
	EiffelClass* ec;
	EiffelArray* ea;

	switch(this->type->tree_node->type) {
	
		case VoidV:
			//Выдать ошибку?
			break;
		case ClassV:
			/* EiffelClass* */ ec = (EiffelClass*)this->type;
			//result += "L" + ec->className + ";";
			break;
		case ArrayV:
			result += "[";
			this->createDescriptor();
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
		default:
			result += "<unknownType!>";	//unknown
			return result;
	}
	
	return result;
}
