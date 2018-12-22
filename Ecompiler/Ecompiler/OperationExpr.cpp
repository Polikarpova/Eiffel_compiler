#include "OperationExpr.h"
#include "Method.h"
#include "BOOLEAN.h"

#include "MethodCall.h"

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

	if ( expr->right ) {
		oe->right = Expression::create(mtd, expr->right);
	}
	
	oe->type = oe->getReturnType();
	bool success = oe->type != NULL; // oe->expressionType();
	if(!success)
		delete oe;

	return success ? oe : 0;
}

EiffelType* OperationExpr::getReturnType( ) {

	//������ ����� (������� ��������)
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

			if ( lType->toReadableString() != "INTEGER" && lType->toReadableString() != "REAL") {

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
						
						//this->type = EiffelProgram::currentProgram->findClass("REAL")->getType();

						getError( rType->toReadableString(), lType->toReadableString() );
						delete rType;
						delete lType;
						return NULL;
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

/*virtual*/ ByteCode& OperationExpr::toByteCode(ByteCode &bc) {

	ByteCode code;

	switch(this->tree_node->type) {
		
		case NotE:
		case UPlusE:
		case UMinusE:
			unaryToByteCode(code);
			break;
		case PowerE:
		case MulE:
		case DivE:
		case PlusE:
		case MinusE:
			arithmeticToByteCode(code);
			break;
		case EqualsE:
		case NotEqualE:
		case LessE:
		case GreaterE:
		case LessOrEqualE:
		case GreaterOrEqualE:
			comparsionToByteCode(code);
			break;
		case AndE:
		case AndThenE:
		case OrE:
		case OrElseE:
		case XORE:
		case ImpliesE:
			logicToByteCode(code);
			break;
		default:
			EiffelProgram::currentProgram->logError(
				QString("internal"), 
				QString("Unknown operation in code"),
				this->tree_node->loc.first_line);
			break; //unknown
	}

	return bc.append(code);
}

ByteCode& OperationExpr::unaryToByteCode(ByteCode &bc) {

	if ( this->tree_node->type == NotE ) {
	
		bc.iconst_(0);
		this->left->toByteCode(bc);
		bc.ifne(+3+2);
		bc.pop().iconst_(1);

		//NExprList args;
		//args.first = this->left->tree_node;
		//args.last = this->left->tree_node;
		//args.loc = this->left->tree_node->loc;

		//MethodCall::create(this->currentMethod, currentMethod->metaClass->findMethod("_1_NotE"), &args)->toByteCode(bc);

	} else if ( this->tree_node->type == UPlusE ) {

		this->left->toByteCode(bc);

	} else if ( this->tree_node->type == UMinusE ) {

		this->left->toByteCode(bc);

		if(this->left->expressionType()->isInteger()) {
			bc.ineg();
		}
		if(this->left->expressionType()->isReal()) {
			bc.fneg();
		}

	} else {
	
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Unknown unary operation in code"),
			this->tree_node->loc.first_line);
	}

	return bc;
}

ByteCode& OperationExpr::arithmeticToByteCode(ByteCode &bc) {

	//���� ��� ����� �������� ��������������
	if ( this->tree_node->type == PowerE || this->tree_node->type == MulE || this->tree_node->type == DivE 
		|| this->tree_node->type == PlusE || this->tree_node->type == MinusE) {
	
		//������ ����� � ������ �����
		this->left->toByteCode(bc);
		this->right->toByteCode(bc);
	
		if ( this->tree_node->type == PowerE ) {

			//����� ������� �� RTL
			if ( this->left->type->isInteger() ) {
		
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"powerI", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			}

		} else if ( this->tree_node->type == MulE ) {
			
			//���� ������������ ����
			if ( this->left->type->isInteger() ) {
		
				bc.imul();
			}
			//���� ��� ����� � ��������� �������
			else {
				bc.fmul();
			}

		} else if ( this->tree_node->type == DivE ) {
	
			//���� ������������ ����
			if ( this->left->type->isInteger() ) {
		
				bc.idiv();
			}
			//���� ��� ����� � ��������� �������
			else {
				bc.fdiv();
			}

		} else if ( this->tree_node->type == PlusE ) {
	
			//���� ������������ ����
			if ( this->left->type->isInteger() ) {

				bc.iadd();
			}
			else if ( this->left->type->isString() ) {
			
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"addS", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			}
			//���� ��� ����� � ��������� �������
			else {
				bc.fadd();
			}

		} else if ( this->tree_node->type == MinusE ) {
		
			//���� ������������ ����
			if ( this->left->type->isInteger() ) {
		
				bc.isub();
			}
			//���� ��� ����� � ��������� �������
			else {
				bc.fsub();
			}
		} 
	
	} else {
	
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Unknown arithmetic operation in code"),
			this->tree_node->loc.first_line);
	}

	return bc;
}

ByteCode& OperationExpr::comparsionToByteCode(ByteCode &bc) {

	if ( this->tree_node->type == EqualsE || this->tree_node->type == NotEqualE || this->tree_node->type == LessE 
		|| this->tree_node->type == GreaterE || this->tree_node->type == LessOrEqualE || this->tree_node->type == GreaterOrEqualE ) {
	
		//������ ����� � ������ �����
		this->left->toByteCode(bc);
		this->right->toByteCode(bc);
	
		if ( this->tree_node->type == EqualsE ) {

			if ( this->left->type->isInteger() ) {
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"equalI", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			} else if ( this->left->type->isReal() ) {
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"equalF", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			} else if ( this->left->type->isString() ) {
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"equalS", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			}

		} else if ( this->tree_node->type == NotEqualE ) {

			if ( this->left->type->isInteger() ) {
				MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
					"notEqualI", 
					QList<Expression*>()
					<< this->left
					<< this->right
				);

				call_helper->toByteCode(bc);
			}

		} else if ( this->tree_node->type == LessE ) {

		} else if ( this->tree_node->type == GreaterE ) {

		} else if ( this->tree_node->type == LessOrEqualE ) {

		} else if ( this->tree_node->type == GreaterOrEqualE ) {

		}
	} else {
	
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Unknown comparsion operation in code"),
			this->tree_node->loc.first_line);
	}

	return bc;
}

ByteCode& OperationExpr::logicToByteCode(ByteCode &bc) {

	if ( this->tree_node->type == AndE || this->tree_node->type == AndThenE || this->tree_node->type == OrE 
		|| this->tree_node->type == OrElseE || this->tree_node->type == XORE || this->tree_node->type == ImpliesE ) {

	
		if ( this->tree_node->type == AndE ) {

		} else if ( this->tree_node->type == AndThenE ) {
			
			//������ �����
			this->left->toByteCode(bc);
			bc.dup();

			int if_start = bc.currentOffset;
			bc.ifeq(0x0000);

			bc.pop();
			this->right->toByteCode(bc);

			bc.gotoPos(if_start + 1)
				.u2(bc.size() - if_start)
				.gotoEnd();

		} else if ( this->tree_node->type == OrE ) {

		} else if ( this->tree_node->type == OrElseE ) {

			//������ �����
			this->left->toByteCode(bc);
			bc.dup();

			int if_start = bc.currentOffset;
			bc.ifne(0x0000);

			bc.pop();
			this->right->toByteCode(bc);

			bc.gotoPos(if_start + 1)
				.u2(bc.size() - if_start)
				.gotoEnd();

		} else if ( this->tree_node->type == XORE ) {

		} else if ( this->tree_node->type == ImpliesE ) {

		}
	} else {
	
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Unknown logic operation in code"),
			this->tree_node->loc.first_line);
	}

	return bc;
}

