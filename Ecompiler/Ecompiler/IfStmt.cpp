#include "IfStmt.h"

IfStmt::IfStmt(void)
{
	this->currentMethod = 0;
	this->generalMethodCall = 0;
	this->condition = 0;
	this->ifBody = 0;
	this->elseif = 0;
	this->elseBody = 0;
}

IfStmt::~IfStmt(void)
{
}

/*static*/ IfStmt* IfStmt::create(Method* mtd, struct NIfStmt* stmt) {

	bool success = true;
	IfStmt* is = new IfStmt();
	is->currentMethod = mtd;

	//��������� �������
	is->condition = Expression::create(mtd, stmt->thenPart->first->cond);

	if ( !is->condition ) {
		delete is;
		return 0;
	} else {
	
		if ( is->condition->expressionType()->isVoid() ) {
		
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Condition is not an expression. Procedure %1 does not return a value")
					.arg(is->condition->tree_node->value.id),
				is->condition->tree_node->loc.first_line);
			delete is;
			return 0;
		}
		else if ( is->condition->expressionType()->toReadableString() != "BOOLEAN" ) {

			EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Condition is not a BOOLEAN expression. cannot convert type %1 into BOOLEAN.")
						.arg(is->condition->expressionType()->toReadableString()),
					is->condition->tree_node->loc.first_line);
			delete is;	
			return 0;
		}
	}

	//���������� ����� ������ then
	is->ifBody = new StatementBlock(mtd);
	is->ifBody->createBody(stmt->thenPart->first->stmtList);
	
	//���� ��� ������ if
	if ( stmt->thenPart->first == stmt->thenPart->last && !stmt->elsePart ) {
		//�� ������
	}
	//��� ������� if-else
	else if ( stmt->thenPart->first == stmt->thenPart->last && stmt->elsePart ) {
		
		is->elseBody = new StatementBlock(mtd);
		is->elseBody->createBody(stmt->elsePart->stmtList);
	}
	//��� ������������ �����
	else if ( stmt->thenPart->first != stmt->thenPart->last ) {
	
		struct NThenPartList thenPartList;
		thenPartList.first = stmt->thenPart->first->next;
		thenPartList.last = stmt->thenPart->last;
		thenPartList.loc = stmt->thenPart->loc;

		struct NIfStmt innerStmt;
		innerStmt.loc = stmt->loc;
		innerStmt.thenPart = &thenPartList;
		innerStmt.elsePart = stmt->elsePart;

		//�������� �� ���������� IfStmt
		is->elseif = IfStmt::create( mtd, &innerStmt);

		if ( ! is->elseif ) {
		
			success = false;
		}
	}

	return success ? is : 0;
}

/*virtual*/ ByteCode& IfStmt::toByteCode(ByteCode &bc) {

	int if_start = 0, goto_start = 0;

	ByteCode code;

	code.log("Calculate condition");
	this->condition->toByteCode(code);

	//���� ��������� condition false ��������� � (1)
	//	(��� ��� ��� BOOLEAN, ����� �� ������ �������� ��������� � 0?)
	if_start = code.currentOffset; //���������� ����� ������ ����������� (1)
	code.ifeq(0x0666);	//���� ��� �����

	code.log("Write if-block to byte-code");
	this->ifBody->toByteCode(code);

	//���� ��� ������ if
	if ( !elseif && !elseBody ) {
		
		//����� ������ ������ �� �����
		int length = +(code.currentOffset - if_start);
		code.gotoPos(if_start+1)
			.u2(length)
			.gotoEnd();
	}
	else if ( elseif && elseBody) {
		code.log("Very-very bad");

		//������

	} else {
		
		//����� goto
		goto_start = code.currentOffset;		
		code.goto_(0x0000); //���� �����

		//��������� (1) � ������� if
		int lenght = +(code.currentOffset - if_start);
		code.gotoPos(if_start+1)
			.u2(lenght)
			.gotoEnd();

		if ( !elseif && elseBody ) {
			code.log("Write else-block to byte-code");
			this->elseBody->toByteCode(code);
		}

		if ( elseif && !elseBody ) {
		
			code.log("Write else-block to byte-code");
			this->elseif->toByteCode(code);
		}

		//��������� ����� �������� � goto
		lenght = +(code.currentOffset - goto_start);
		code.gotoPos(goto_start+1)
			.u2(lenght)
			.gotoEnd();	
	}

	return bc.append(code);
}

/*
	//���� ��� ������ if
	if ( !elseif && !elseBody ) {
		
		//����� ������ ������ �� �����
	}
	//��� ������� if-else
	else if ( !elseif && elseBody ) {
		
		//����� goto
		code->goto_(0x0000); //���� �����
		goto_start = code->currentOffset - 2;

		//��������� ����� � ������� if
		int lenght = +(code->currentOffset - if_start - 1);
		code->gotoPos(if_start)
			.u2(lenght)
			.gotoEnd();

		code->log("Write else-block to byte-code");
		this->elseBody->toByteCode(*code);

		//��������� ����� �������� � goto
		lenght = +(code->currentOffset - goto_start - 1);
		code->gotoPos(goto_start)
			.u2(lenght)
			.gotoEnd();
	}
	//��� ������������ �����
	else if ( elseif && !elseBody ) {
	
		//����� goto
		code->goto_(0x0000); //���� �����
		goto_start = code->currentOffset - 2;

		//��������� ����� � ������� if
		int lenght = +(code->currentOffset - if_start - 1);
		code->gotoPos(if_start)
			.u2(lenght)
			.gotoEnd();

		code->log("Write else-block to byte-code");
		this->elseif->toByteCode(*code);

		//��������� ����� �������� � goto
		lenght = +(code->currentOffset - goto_start - 1);
		code->gotoPos(goto_start)
			.u2(lenght)
			.gotoEnd();
		
	} else {
		code->log("Very-very bad");
	}
*/