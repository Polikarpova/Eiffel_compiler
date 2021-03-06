#include "CreateStmt.h"

#include "Method.h"
#include "Expression.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

CreateStmt::CreateStmt(void)
{
	this->generalMethodCall = NULL;
	this->leftOfDot = NULL;
}
CreateStmt::~CreateStmt(void)
{
}


/** mtd - �����, ��� �� ����������
	��� ������� ������� �� ������  `fromRefnCall`  � Expression.cpp
*/
MethodCall* fromRefnCall(Method* mtd, struct NExpr* node);




/*static*/ CreateStmt* CreateStmt::create(Method* mtd, struct NExpr* expr) {

	//mtd - �����, ��� �� ����������
	//m - �����, ������� ������
	MethodCall* general_method_call = NULL;

	bool success = false;

	//�������� �� ����������
	if ( expr->type != RefnCallE ) {
	
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Invalid constructor call"),
			expr->loc.first_line);
	
		return NULL;

	} else {
	
		general_method_call = fromRefnCall(mtd, expr);
	}

	if( ! general_method_call )
		return NULL;

	// set tree_node : use of tree_node->loc
	general_method_call->tree_node = expr;

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

	// make assignment
	success = leftOfDot->setRightValue(general_method_call , /*force =*/ true );

	if( ! success ) {

		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Constructor `%1` must be called on assignable expression.")
				.arg(general_method_call->calledMethod->name),
			expr->loc.first_line);
	
		return NULL;
	}

	if(leftOfDot->type->isArray())
	{
		// init constants for array creation
		EiffelType* elem_type = ((EiffelArray*)leftOfDot->type)->elementType;
		general_method_call->createArrayElemConstants(elem_type);
	}

	general_method_call->left = NULL;
	general_method_call->noQualify = true;

	CreateStmt* cs = new CreateStmt();

	cs->currentMethod = mtd;
	cs->leftOfDot = leftOfDot;
	cs->generalMethodCall = general_method_call;

	// !! prepend bytecode: creation to general_method_call !!

	return success? cs : NULL;
}

ByteCode& CreateStmt::toByteCode(ByteCode &bc)
{
	// ������� ����������� ����: ��������� � ������
	return this->leftOfDot->toByteCode(bc);
}
