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
				
				getError(/*"NOT",*/ typeName, "BOOLEAN");
			}

		} else {
		
			//проверка UPLUS UMINUS
			//получаем тип
			this->type = this->left->expressionType();

			const char* typeName = typeid(this->type).name();

			if ( typeName != "INTEGER" || typeName != "REAL") {
				
				//getError( (this->tree_node->type == UPlusE) ? "Unary plus" : "Unary minus", typeName, "INTEGER");
				getError( typeName, "INTEGER or REAL");
				
			}
		}

	} else if ( this->left && this->right ) {
	

		//проверка на всё остальное
		EiffelType* lType = this->left->expressionType();
		EiffelType* rType = this->right->expressionType();

		if ( this->tree_node->type == PlusE || this->tree_node->type == MinusE || this->tree_node->type == MulE || this->tree_node->type == DivE || this->tree_node->type == PowerE ) {
		
			//доп проверка на строки у операции +
			/*if (this->tree_node->type == PlusE ) {
				 
				if ( typeid(lType).name() != "STRING" && typeid(rType).name() != "STRING" ) {
					
					getError( QString(typeid(lType).name()) + QString(" or ") + QString(typeid(rType).name()), "STRING");
				}
			}*/

			if ( (typeid(lType).name() != "INTEGER" && typeid(rType).name() != "INTEGER") || (typeid(lType).name() != "REAL" && typeid(rType).name() != "REAL") ) {
				
				getError( QString(typeid(lType).name()) + QString(" or ") + QString(typeid(rType).name()), "INTEGER or REAL");

			}

			if ( typeid(lType).name() == "INTEGER" ) {
				type = lType;
			}
		}
	}

	return this->type;
}

EiffelType* OperationExpr::getError( /*QString operType, */QString actualType, QString expectedType ) {

	type = 0;
	EiffelProgram::currentProgram->logError(
		QString("semantic"), 
		QString("Invalid operands in routine %1.%2. Type %3 cannot be converted into %4")
			.arg(/*operType,*/ this->currentMethod->metaClass->name(), this->currentMethod->name, actualType, expectedType),
			this->tree_node->loc.first_line);
	return NULL;
}
