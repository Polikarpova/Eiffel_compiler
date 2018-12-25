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

/*virtual*/ bool EiffelArray::canCastTo(const EiffelType* otherType, EiffelType* *convertTo /*= 0*/) const
{
	// преобразование не требуется
	convertTo = 0;

	if( ! otherType->isArray() )
	{
		return false;
	}


	EiffelType* convertType = 0;

	bool b = this->elementType->canCastTo( ((EiffelArray*)otherType)->elementType, &convertType );
	
	// требуется явное преобразование (нет прямой [ссылочной] совместимости)
	if(convertType != 0)
	{
		return false;
	}

	return b;
}
