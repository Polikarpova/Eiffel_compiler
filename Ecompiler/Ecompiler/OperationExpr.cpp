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
				
				getError(typeName, "BOOLEAN");
				return NULL;
			}

		} else {
		
			//проверка UPLUS UMINUS
			//получаем тип
			this->type = this->left->expressionType();

			const char* typeName = typeid(this->type).name();

			if ( typeName != "INTEGER" || typeName != "REAL") {
				
				getError( typeName, "INTEGER or REAL");
				return NULL;
			}
		}

	} else if ( this->left && this->right ) {
	

		//проверка на всё остальное
		EiffelType* lType = this->left->expressionType();
		EiffelType* rType = this->right->expressionType();

		if ( this->tree_node->type == PlusE || this->tree_node->type == MinusE || this->tree_node->type == MulE || this->tree_node->type == DivE || this->tree_node->type == PowerE ) {
		
			//доп проверка на строки у операции +
			if (this->tree_node->type == PlusE ) {
				 
				if ( typeid(lType).name() == "STRING" || typeid(rType).name() == "STRING" ) {
					
					getError( QString(typeid(lType).name()) + QString(" or ") + QString(typeid(rType).name()), "STRING");
					delete rType;
					delete lType;
					return NULL;
				}
			}


			if ( typeid(lType).name() != "INTEGER" || typeid(lType).name() != "REAL") {
				getError( QString(typeid(lType).name()), "INTEGER or REAL");
				delete rType;
				delete lType;
				return NULL;

			} else {
			
				if ( typeid(rType).name() != typeid(lType).name() ) {

					//Если справа char или boolean, то ошибочка
					if ( typeid(rType).name() == "BOOLEAN" || typeid(rType).name() == "CHARACTER" ) {
						getError( QString(typeid(rType).name()), QString(typeid(lType).name()));
						delete rType;
						delete lType;
						return NULL;

					} else {
					
						//преобразование int в real
						//здесь надо узнать кто int, перевести его в real и возвразаем мы real в итоге
						
						this->type = rType;  //к этому моменту он должен быть переведен к типу REAL
					}
				}
			}
		}
	}

	return this->type;
}

void OperationExpr::getError( QString actualType, QString expectedType ) {

	type = 0;
	EiffelProgram::currentProgram->logError(
		QString("semantic"), 
		QString("Invalid operands in routine %1.%2. Type %3 cannot be converted into %4")
			.arg(/*operType,*/ this->currentMethod->metaClass->name(), this->currentMethod->name, actualType, expectedType),
			this->tree_node->loc.first_line);
}
