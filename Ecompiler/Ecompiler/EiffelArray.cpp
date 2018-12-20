#include "EiffelArray.h"

/*static*/ EiffelArray* EiffelArray::create(struct NType* node) {

	EiffelProgram* program = EiffelProgram::currentProgram;

	EiffelArray* ea = 0;

	switch(node->type) {
	
		case ArrayV:
			ea = new EiffelArray(
				EiffelType::create(node->itemType) // recurse
				);
			if(ea == NULL)
			{
				program->logError(
					QString("semantic"), 
					QString("Error parsing array type."),
					node->loc.first_line);
			}
		default:
			//mc = new IntegerType();
			break;
	}

	//if( !ea )
	//	return NULL;

	return ea;
}