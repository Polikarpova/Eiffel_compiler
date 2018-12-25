#include "ArrayElemRef.h"
#include "EiffelArray.h"
#include "Method.h"


ArrayElemRef::ArrayElemRef(void)
	: Expression()
{
	indexExpr = NULL;
}


ArrayElemRef::~ArrayElemRef(void)
{
}

/*static*/ ArrayElemRef* ArrayElemRef::create(Method* mtd, struct NExpr* node)
{
	if(!node)
		return 0;

	Expression* arrayExpr;
	Expression* indexExpr;

	arrayExpr = Expression::create(mtd, node->left);
	indexExpr = Expression::create(mtd, node->right);

	if(arrayExpr == NULL) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Error occured while analyzing left of `[..]`. (In routine: %1.%2)")
				.arg(mtd->metaClass->name(), mtd->name),
			node->loc.first_line);
		return NULL;
	}
	if(indexExpr == NULL) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Error occured while analyzing index expression: `[..]`. Type of array: %3. (In routine: %1.%2)")
				.arg(mtd->metaClass->name(), mtd->name, arrayExpr->expressionType()->toReadableString()),
			node->loc.first_line);
		return NULL;
	}
		
	return ArrayElemRef::create(mtd, arrayExpr, indexExpr);
}

/*static*/ ArrayElemRef* ArrayElemRef::create(Method* mtd, Expression* arrayExpr, Expression* indexExpr)
{
	// check
	if( ! arrayExpr->expressionType()->isArray() )
	{
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Cannot subscript an expression which is not an array. Type of expression: `%1`")
				.arg(arrayExpr->expressionType()->toReadableString()),
			arrayExpr->tree_node->loc.first_line);
		return NULL;
	}
	if( ! indexExpr->expressionType()->isInteger() )
	{
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Invalid expression for index of array: non-INTEGER type. Type of expression: `%1`")
				.arg(indexExpr->expressionType()->toReadableString()),
			indexExpr->tree_node->loc.first_line);
		return NULL;
	}

	ArrayElemRef* aer = new ArrayElemRef();
	aer->currentMethod = mtd;
	aer->left  = arrayExpr;
	aer->indexExpr = indexExpr;

	aer->type = ((EiffelArray*)arrayExpr->type)->elementType;

	// report creation
	qDebug("created ArrayElemRef for: %s", arrayExpr->expressionType()->toReadableString().toLocal8Bit().data());
	return aer;
}

/*virtual*/ bool ArrayElemRef::setRightValue(Expression* r, bool force /*= false*/)
{
	_isLeftValue = false;

	if ( force || ! r->expressionType()->isVoid() ) {
			
		EiffelType* rType = r->expressionType();
		EiffelType* lType = this->expressionType();

		if ( !force && !rType->canCastTo(lType) ) {
		
		//если типы не совпадают, то всё плохо
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Invalid assignment: cannot convert type %1 into type %2")
					.arg(rType->toReadableString(), lType->toReadableString()),
				r->tree_node->loc.first_line);
			return false;
		}

		this->right = r;
		this->_isLeftValue = true;

	} else {
		
		if ( r->tree_node->type == RefnCallE ) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Source of assignment is not an expression. Procedure %1 does not return a value.")
					.arg(r->tree_node->value.id),
				r->tree_node->loc.first_line);
			return false;
		} else {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Source of assignment is not an expression."),
				r->tree_node->loc.first_line);
			return false;
		}
	}

	return _isLeftValue;
}

ByteCode& ArrayElemRef::toByteCode(ByteCode &bc)
{
	// load a reference to an array ...
	// call qualification as this->left
	if(this->left)
		this->left->toByteCode(bc); // load qualification
	else
		throw "Error in ArrayElemRef::toByteCode()"; // cannot be used without qualification


	this->indexExpr->toByteCode(bc); // load index


	if(this->isLeftValue()) // eiffel code:   left := right
	{
		this->right->toByteCode(bc); // load right value to store in the field
		if(this->type->isReference())
			bc.aastore();
		else if(this->type->isInteger())
			bc.iastore();
		else if(this->type->isReal())
			bc.fastore();
	}
	else
	{
		if(this->type->isReference())
			bc.aaload();
		else if(this->type->isInteger())
			bc.iaload();
		else if(this->type->isReal())
			bc.faload();
	}

	return applyI2F(bc);
}

