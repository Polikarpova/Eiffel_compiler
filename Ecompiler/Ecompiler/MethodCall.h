#pragma once
#include "Expression.h"
#include "QList"

class Method;

class MethodCall : public Expression
{

public:
	MethodCall(void);
	~MethodCall(void);

	/*fields*/

	short int methodref_constN, class_of_called_mtd_constN;
	bool noCreate;

	//* �����, � �������� ������������ ������
	Method* calledMethod;

	//* ������ ���������� ������
	QList<Expression*> arguments;


	/*methods*/
	static MethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );

	void createMethodRef(Method* calledMethod);

	// ��� ��������� ������, ��� ����� �.�. �������������: ������������ invokespecial ������ invokevirtual
	// noQualify: �������� �������� ������ �� ������
	ByteCode& toByteCode(ByteCode &, bool noQualify);
	ByteCode& toByteCode(ByteCode &bc) {return toByteCode(bc, false); };


	ByteCode& generateCreation(ByteCode &);
	ByteCode& arrayCreation(ByteCode &);

};
