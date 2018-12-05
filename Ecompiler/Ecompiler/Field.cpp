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

	bool success = false;
	Field* fd = NULL;

	return success? fd : NULL;
}

QString Field::createDescriptor(EiffelType* type) {

	QString result = "";
	

	EiffelClass* ec;

	switch(this->type->tree_node->type) {
	
		case VoidV:
			//������ ������?
			break;
		case ClassV:
			/* EiffelClass* */ ec = (EiffelClass*)this->type;
			result += "L" + ec->className + ";";
			break;
		case ArrayV:
			result += "[";
			EiffelArray* ea = (EiffelArray*)type;
			this->createDescriptor(ea->elementType);
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
