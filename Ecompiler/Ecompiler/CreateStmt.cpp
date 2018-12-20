#include "CreateStmt.h"

#include "Method.h"
#include "Expression.h"
#include "EiffelClass.h"

CreateStmt::CreateStmt(void)
{
	this->generalMethodCall = NULL;
	this->leftOfDot = NULL;
}
CreateStmt::~CreateStmt(void)
{
}


/** mtd - метод, где всё происходит
	Эта функция сделана на основе  `fromRefnCall`  в Expression.cpp
*/
MethodCall* fromRefnCall(Method* mtd, struct NExpr* node);




/*static*/ CreateStmt* CreateStmt::create(Method* mtd, struct NExpr* expr) {

	//mtd - метод, где всё происходит
	//m - метод, который вызван
	MethodCall* general_method_call;

	bool success = false;

	//проверка на ошибулечки
	if ( expr->type != RefnCallE ) {
	
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Invalid procedure call"),
			expr->loc.first_line);
	
		return NULL;

	} else {
	
		general_method_call = fromRefnCall(mtd, expr);
	}

	if( ! general_method_call )
		return NULL;

	if ( ! general_method_call->calledMethod->isCreator )
	{
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Cannot use ordinal procedure `%1` as constructor.")
				.arg(general_method_call->calledMethod->name),
			expr->loc.first_line);
	
		return NULL;
	}

	Expression* leftOfDot = general_method_call->left;

	if ( leftOfDot == NULL )
	{
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Constructor `%1` must be called on object reference like `MyObj.%1`")
				.arg(general_method_call->calledMethod->name),
			expr->loc.first_line);
	
		return NULL;
	}

	success = leftOfDot->setRightValue(general_method_call);

	if( ! success ) {

		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Constructor `%1` must be called on assignable expression.")
				.arg(general_method_call->calledMethod->name),
			expr->loc.first_line);
	
		return NULL;
	}

	general_method_call->left = NULL;

	CreateStmt* cs = new CreateStmt();

	cs->currentMethod = mtd;
	cs->leftOfDot = leftOfDot;
	cs->generalMethodCall = general_method_call;

	// !! prepend bytecode: creation to general_method_call !!

	return success? cs : NULL;
}

ByteCode& CreateStmt::toByteCode(ByteCode &bc)
{
	// вызвать нижележащий узел: обращение к методу
	return this->leftOfDot->toByteCode(bc);
}
