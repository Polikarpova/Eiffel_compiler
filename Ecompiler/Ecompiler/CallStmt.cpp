#include "CallStmt.h"


CallStmt::CallStmt(void)
{
}


CallStmt::~CallStmt(void)
{
}

/*static*/ CallStmt* CallStmt::create(Method* mtd, struct NExpr* expr) {

	bool success = false;
	CallStmt* cs = new CallStmt();

	//�������� �� ����������
	//if ( )

	//��������� ����� � ���� ���������

	//�������� ������������ ���������� � ����� ���������

	success = true;

	return success? cs : 0;

}