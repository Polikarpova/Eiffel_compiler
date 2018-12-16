#include "OperationExpr.h"
#include "Method.h"

OperationExpr::OperationExpr(void)
	: Expression()
{
}


OperationExpr::~OperationExpr(void)
{
}

/*static*/ OperationExpr* OperationExpr::create(Method* mtd, struct NExpr* expr)
{
	OperationExpr* oe = new OperationExpr();

	oe->currentMethod = mtd;
	oe->tree_node = expr;
	oe->left = Expression::create(mtd, expr->left);
	oe->right = Expression::create(mtd, expr->right);

	return oe;
}

EiffelType* OperationExpr::getReturnType( ) {

	//только слева
	if ( this->left && !this->right ) {
	
		if ( this->tree_node->type == NotE) {
		
			//проверка на NOT

			//получаем тип
			this->type = this->left->expressionType();

			const char* typeName = typeid(this->type).name();

			if ( typeName != "BOOLEAN" ) {
				
				getError("NOT", typeName, "BOOLEAN");
			}

		} else {
		
			//проверка UPLUS UMINUS
			//получаем тип
			this->type = this->left->expressionType();

			const char* typeName = typeid(this->type).name();

			if ( typeName != "INTEGER") {
				
				getError( (this->tree_node->type == UPLUS) ? "Unary plus" : "Unary minus", typeName, "INTEGER");
			} else if ( typeName != "REAL") {
				
				getError( (this->tree_node->type == UPLUS) ? "Unary plus" : "Unary minus", typeName, "REAL");
			}
		}

	} else if ( this->left && this->right ) {
	

		//проверка на всё остальное
	}

	return this->type;
}

EiffelType* OperationExpr::getError( QString operType, QString actualType, QString expectedType ) {

	EiffelProgram::currentProgram->logError(
		QString("semantic"), 
		QString("Invalid operands for operation %1 in routine %2.%3. Type %4 cannot be converted into %5")
			.arg(operType, this->currentMethod->metaClass->name(), this->currentMethod->name, actualType, expectedType),
			this->tree_node->loc.first_line);
	return NULL;
}
