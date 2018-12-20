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
	bool success = oe->expressionType();

	return success ? oe : 0;
}

EiffelType* OperationExpr::getReturnType( ) {

	//������ �����
	if ( this->left && !this->right ) {
	
		if ( this->tree_node->type == NotE) {
		
			//�������� �� NOT

			//�������� ���
			this->type = this->left->expressionType();

			if ( this->type->toReadableString() != "BOOLEAN" ) {
				
				getError( this->type->toReadableString(), "BOOLEAN");
				return NULL;
			}

		} else {
		
			//�������� UPLUS UMINUS
			//�������� ���
			this->type = this->left->expressionType();

			if ( this->type->toReadableString() != "INTEGER" || this->type->toReadableString() != "REAL") {
				
				getError( this->type->toReadableString(), "INTEGER or REAL");
				return NULL;
			}
		}

	} else if ( this->left && this->right ) {
	

		//�������� �� �� ���������
		EiffelType* lType = this->left->expressionType();
		EiffelType* rType = this->right->expressionType();

		//�������������� ��������
		if ( this->tree_node->type == PlusE || this->tree_node->type == MinusE || this->tree_node->type == MulE || this->tree_node->type == DivE || this->tree_node->type == PowerE ) {

			if ( lType->toReadableString() != "INTEGER" || lType->toReadableString() != "REAL") {

				//��� �������� �� ������ � �������� +
				if ( this->tree_node->type == PlusE && ( lType->toReadableString() == "STRING" || rType->toReadableString() == "STRING") ) {

					if ( rType->toReadableString() != "STRING") {
						
						getError( rType->toReadableString(), "STRING");
						delete rType;
						delete lType;
						return NULL;
					} else if ( lType->toReadableString() != "STRING") {
						
						getError( lType->toReadableString(), "STRING");
						delete rType;
						delete lType;
						return NULL;
					} else {
					
						this->type = EiffelProgram::currentProgram->findClass("STRING")->getType();
					}

				} else {
					getError( lType->toReadableString(), "INTEGER or REAL");
					delete rType;
					delete lType;
					return NULL;
				}

			} else {
			
				if ( rType->toReadableString() != lType->toReadableString() ) {

					//���� ������ char ��� boolean ��� string, �� ��������
					if ( rType->toReadableString() == "BOOLEAN" || rType->toReadableString() == "CHARACTER" || rType->toReadableString() == "STRING") {
						getError( rType->toReadableString(), lType->toReadableString() );
						delete rType;
						delete lType;
						return NULL;

					} else {
					
						//�������������� int � real
						//����� ���� ������ ��� int, ��������� ��� � real � ���������� �� real � �����
						
						this->type = EiffelProgram::currentProgram->findClass("REAL")->getType();
					}
				} else {
				
					this->type = lType;
				}
			}
		}
		//���������: = /=
		else if ( this->tree_node->type == EqualsE || this->tree_node->type == NotEqualE ) {
		
			//������������ �� �� ����
			//���� ���� ���� �� ���������....
			if ( rType->toReadableString() != lType->toReadableString() ) {
				qDebug("Use diffrent operands  in operation = or /=");
			}

			//������ ���������� boolean
			this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
		}
		//< > <= >=
		else if ( this->tree_node->type == LessE || this->tree_node->type == GreaterE || this->tree_node->type == LessOrEqualE || this->tree_node->type == GreaterOrEqualE ) {
		
			//��� � �����
			//����� � �����
			//��� � ���
			//������ �� ������

			if ( lType->toReadableString() == "BOOLEAN" ) {
				
				getError( lType->toReadableString(), "INTEGER or REAL or CHARACTER or STRING");
				delete rType;
				delete lType;
				return NULL;
			}

			if ( rType->toReadableString() == "BOOLEAN") {
				
				getError( rType->toReadableString() , "INTEGER or REAL or CHARACTER or STRING");
				delete rType;
				delete lType;
				return NULL;
			}

			if ( rType->toReadableString() != lType->toReadableString() ) {
				
				getError( rType->toReadableString() , lType->toReadableString() );
				delete rType;
				delete lType;
				return NULL;
			}

			//���������� bool
			this->type = EiffelProgram::currentProgram->findClass("BOOLEAN")->getType();
		}
		//OR OR_ELSE XOR AND AND_THEN IMPLIES
		else if ( this->tree_node->type == AndE || this->tree_node->type == AndThenE || this->tree_node->type == OrE || this->tree_node->type == OrElseE || this->tree_node->type == XORE || this->tree_node->type == ImpliesE ) {
		
			//������ bool � bool, ���������� bool
			if ( ( lType->toReadableString() != "BOOLEAN" || rType->toReadableString() != "BOOLEAN") && rType->toReadableString() != lType->toReadableString() ) {
				
				if ( lType->toReadableString() != "BOOLEAN" ) {
					getError( lType->toReadableString() , "BOOLEAN");
					delete rType;
					delete lType;
					return NULL;
				}

				if ( rType->toReadableString() != "BOOLEAN" ) {
					getError( rType->toReadableString(), "BOOLEAN");
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
