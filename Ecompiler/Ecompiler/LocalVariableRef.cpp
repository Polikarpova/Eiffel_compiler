#include "LocalVariableRef.h"
#include "LocalVariable.h"


LocalVariableRef::LocalVariableRef(void)
	: Expression()
{
	this->locVar = 0;
	this->type = 0;
}


LocalVariableRef::~LocalVariableRef(void)
{
}

/*static*/ LocalVariableRef* LocalVariableRef::create(Method* mtd, LocalVariable* locVar) {
	LocalVariableRef* lvr = new LocalVariableRef();
	lvr->currentMethod = mtd;
	lvr->locVar = locVar;
	lvr->type = locVar->type;
	return lvr;
}

ByteCode& LocalVariableRef::toByteCode(ByteCode &bc)
{
	if(this->isLeftValue()) // eiffel code:   left := right
	{
		this->right->toByteCode(bc); // load right value to store in the field
		if(this->type->isReference())
			bc.astore_auto(this->locVar->n);
		else if(this->type->isInteger())
			bc.istore(this->locVar->n);
	}
	else
	{
		if(this->type->isReference())
			bc.aload_auto(this->locVar->n);
		else if(this->type->isInteger())
			bc.iload(this->locVar->n);
	}

	return bc;
}

/*virtual*/ bool LocalVariableRef::setRightValue(Expression* r, bool force /*= false*/)
{
	this->_isLeftValue = false;

	//EiffelType *lType = this->type;
	//EiffelType *rType = r->expressionType();

	//if ( ! lType->canCastTo( rType ) ) {
	//	
	////	EiffelProgram::currentProgram->logError(
	////		QString("semantic"), 
	////		QString("Invalid assignment: cannot convert type from `%1` to `%2`.")
	////			.arg(rType->toReadableString(), lType->toReadableString()),
	////		r->tree_node->loc.first_line);
	//	return false;
	//}

	this->right = r;
	this->_isLeftValue = true;

	return this->_isLeftValue;
}