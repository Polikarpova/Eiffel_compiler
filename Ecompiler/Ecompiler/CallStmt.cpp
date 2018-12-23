#include "CallStmt.h"

#include "Method.h"
#include "Expression.h"
#include "EiffelClass.h"

CallStmt::CallStmt(void)
{
}
CallStmt::~CallStmt(void)
{
}


/** mtd - �����, ��� �� ����������
	��� ������� ������� �� ������  `fromRefnCall`  � Expression.cpp
	(����������� ������ ��������� ����: ����� �������, ��������� ���� �����������)
*/
MethodCall* fromRefnCall(Method* mtd, struct NExpr* node)
{
	if(!node)
		return 0;

	QString id(node->value.id);
	id = id.toLower();

	Expression* qualification_expr = 0;
	MetaClass* qualification_class = 0;

	if(node->left == NULL)	// ��� ������������
	{
		// ��������� � ����� �������� ������ (������� Current)
		qualification_class = mtd->metaClass;
	}
	else // Check Qualification as `node->left`
	{
		qualification_expr = Expression::create(mtd, node->left);

		if(qualification_expr == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Error occured while analyzing left of `.%1`. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		
		// find out type & class of left expr
		EiffelType* et = qualification_expr->expressionType();

		if( dynamic_cast<EiffelClass*>(et) != nullptr ) {
			qualification_class = ((EiffelClass*) et)->metaClass;
		}
		else {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Left of `.%1` is not an object (cannot call anything on it). (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
	}

	// check if the feature exists if qualification_class class

	Feature* called_feature = qualification_class->findFeature(id);

	if(called_feature == NULL) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Using undefined feature `%1` of class `%4`. (In routine: %2.%3)")
				.arg(id, mtd->metaClass->name(), mtd->name, qualification_class->name()),
			node->loc.first_line);
		return NULL;
	}

	if( ! called_feature->isExportedTo(mtd->metaClass) ) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Cannot use feature `%1` of class `%4`: it is not exported to class `%2`. (In routine: %2.%3)")
				.arg(id, mtd->metaClass->name(), mtd->name, qualification_class->name()),
			node->loc.first_line);
		return NULL;
	}

	if( called_feature->isField() ) // feature is a field
	{
		if(node->ExprList != NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Calling to field (`%1`) is not allowed. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		else	// ������������ ������� ��� ����: ��� ����������
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Access to field (`%1`) is not a valid statement. Use procedure instead. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
	}

	if( called_feature->isMethod() ) // feature is a method
	{
		if( ! called_feature->isVoid() ) // Non-Void (Value) method
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Invalid procedure call: routine `%1` is a function, procedure expected. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		else
		{
			// create MethodCall. Parameters: (Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification /*= NULL*/ )
			MethodCall* mtdc = MethodCall::create(mtd, (Method*)called_feature, node->ExprList, qualification_expr);
			if(mtdc) mtdc->tree_node = node;
			return mtdc;
			// finish
		}
	}
	else
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Cannot identify feature `%1` of class `%4` as neither attribute nor procedure. (In routine: %2.%3)")
				.arg(id, mtd->metaClass->name(), mtd->name, qualification_class->name()),
			node->loc.first_line);
		return NULL;
	}

	return NULL;
}


// ��������� � Expression.cpp
extern MethodCall* fromPrecursor(Method* mtd, struct NExpr* node);

/*static*/ CallStmt* CallStmt::create(Method* mtd, struct NExpr* expr) {

	//mtd - �����, ��� �� ����������
	//m - �����, ������� ������
	MethodCall* general_method_call;

	bool success = false;

	//�������� �� ����������
	if ( expr->type == PrecursorE ) {

		general_method_call = fromPrecursor(mtd, expr);

	} else if ( expr->type == RefnCallE ) {
	
		general_method_call = fromRefnCall(mtd, expr);

	} else {
	
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Invalid procedure call"),
			expr->loc.first_line);
	
		return NULL;
	}

	if( ! general_method_call )
		return NULL;

	/*if ( general_method_call->calledMethod->isCreator ) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Call to constructor `%1`: `CREATE` mark not specified. Creating type: %2.")
				.arg(general_method_call->calledMethod->name, general_method_call->type->toReadableString()),
			expr->loc.first_line);
	
		return NULL;
	}*/

	// disable costructors` creation skill
	general_method_call->noCreate = true;

	success = true;

	CallStmt* cs = new CallStmt();

	cs->currentMethod = mtd;
	cs->generalMethodCall = general_method_call;

	return success? cs : NULL;
}

ByteCode& CallStmt::toByteCode(ByteCode &bc)
{
	// ������� ����������� ����: ��������� � ������
	return generalMethodCall->toByteCode(bc);
}
