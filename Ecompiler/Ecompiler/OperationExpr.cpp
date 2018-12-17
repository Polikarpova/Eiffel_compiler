#include "OperationExpr.h"
#include "Method.h"
#include "BOOLEAN.h"

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
	

		//проверка на всЄ остальное
		EiffelType* lType = this->left->expressionType();
		EiffelType* rType = this->right->expressionType();

		//арифметические операции
		if ( this->tree_node->type == PlusE || this->tree_node->type == MinusE || this->tree_node->type == MulE || this->tree_node->type == DivE || this->tree_node->type == PowerE ) {

			if ( typeid(lType).name() != "INTEGER" || typeid(lType).name() != "REAL") {

				//доп проверка на строки у операции +
				if ( this->tree_node->type == PlusE && (typeid(lType).name() == "STRING" || typeid(rType).name() == "STRING") ) {
				
					if ( typeid(rType).name() != "STRING") {
						
						getError( QString(typeid(rType).name()), "STRING");
						delete rType;
						delete lType;
						return NULL;
					} else if ( typeid(lType).name() != "STRING") {
						
						getError( QString(typeid(lType).name()), "STRING");
						delete rType;
						delete lType;
						return NULL;
					} else {
					
						this->type = EiffelProgram::currentProgram->findClass("STRING")->getType();
					}

				} else {
					getError( QString(typeid(lType).name()), "INTEGER or REAL");
					delete rType;
					delete lType;
					return NULL;
				}

			} else {
			
				if ( typeid(rType).name() != typeid(lType).name() ) {

					//≈сли справа char или boolean или string, то ошибочка
					if ( typeid(rType).name() == "BOOLEAN" || typeid(rType).name() == "CHARACTER" || typeid(rType).name() == "STRING") {
						getError( QString(typeid(rType).name()), QString(typeid(lType).name()));
						delete rType;
						delete lType;
						return NULL;

					} else {
					
						//преобразование int в real
						//здесь надо узнать кто int, перевести его в real и возвразаем мы real в итоге
						
						this->type = EiffelProgram::currentProgram->findClass("REAL")->getType();
					}
				} else {
				
					this->type = lType;
				}
			}
		}
		//сравнение: = /=
		else if ( this->tree_node->type == EqualsE || this->tree_node->type == NotEqualE ) {
		
			//сравниваетс€ всЄ со всем
			//даже если типы не совпадают....
			if ( typeid(rType).name() != typeid(lType).name() ) {
				qDebug("Use diffrent operands  in operation = or /=");
			}

			//всегда возвращает boolean
			this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
		}
		//< > <= >=
		else if ( this->tree_node->type == LessE || this->tree_node->type == GreaterE || this->tree_node->type == LessOrEqualE || this->tree_node->type == GreaterOrEqualE ) {
		
			//инт с интом
			//флоат с флоат
			//чар с чар
			//стринг со стринг

			if ( typeid(lType).name() == "BOOLEAN" /*|| typeid(lType).name() == "BOOLEAN" */) {
				
				getError( QString(typeid(lType).name()), "INTEGER or REAL or CHARACTER or STRING");
				delete rType;
				delete lType;
				return NULL;
			}

			if ( typeid(rType).name() == "BOOLEAN") {
				
				getError( QString(typeid(rType).name()), "INTEGER or REAL or CHARACTER or STRING");
				delete rType;
				delete lType;
				return NULL;
			}

			if ( typeid(rType).name() != typeid(lType).name() ) {
				
				getError( QString(typeid(rType).name()), QString(typeid(lType).name()));
				delete rType;
				delete lType;
				return NULL;
			}

			//возвращает bool
			this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
		}
		//OR OR_ELSE XOR AND AND_THEN IMPLIES
		else if ( this->tree_node->type == AndE || this->tree_node->type == AndThenE || this->tree_node->type == OrE || this->tree_node->type == OrElseE || this->tree_node->type == XORE || this->tree_node->type == ImpliesE ) {
		
			//только bool с bool, возвращает bool
			if ( ( typeid(lType).name() != "BOOLEAN" || typeid(rType).name() != "BOOLEAN") && typeid(rType).name() != typeid(lType).name() ) {
				
				if ( typeid(lType).name() != "BOOLEAN" ) {
					getError( QString(typeid(lType).name()), "BOOLEAN");
					delete rType;
					delete lType;
					return NULL;
				}

				if ( typeid(rType).name() != "BOOLEAN" ) {
					getError( QString(typeid(rType).name()), "BOOLEAN");
					delete rType;
					delete lType;
					return NULL;
				}
			}

			this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
		} else {
		
			type = 0;
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Unknow operation"),
				this->tree_node->loc.first_line);
			delete rType;
			delete lType;
			return NULL;
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
