#include "CreateStmt.h"

#include "Method.h"
#include "Expression.h"
#include "EiffelClass.h"

CreateStmt::CreateStmt(void)
{
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
	MethodCall* general_method_call;

	bool success = false;

	//�������� �� ����������
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

	success = true;

	CreateStmt* cs = new CreateStmt();

	cs->currentMethod = mtd;
	cs->generalMethodCall = general_method_call;

	return success? cs : NULL;
}

ByteCode& CreateStmt::toByteCode(ByteCode &bc)
{
	// ������� ����������� ����: ��������� � ������
	return generalMethodCall->toByteCode(bc);
}
