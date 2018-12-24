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

	short int methodref_constN, class_of_called_mtd_constN, class_of_arr_elem_constN;
	bool noCreate; // ���������� �������� (��������, ������� � ������� `new`)
	bool noQualify; // ���������� �������� ������������
	bool keepNewReferenceOnStack; // ����� �� ������ `dup` ����� `new`
	bool specialCall; // ������������ `invokespecial` ������ `invokevirtual`

	//* �����, � �������� ������������ ������
	Method* calledMethod;

	//* ������ ���������� ������
	QList<Expression*> arguments;
	
	//* ��� �������� �������
	EiffelType* arrayElemType;


	/*methods*/
	static MethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );

	static MethodCall* create(Method* context_mtd, Method* calledMethod, QList<Expression*> arguments/* = QList<Expression*>() */, Expression* qualification = NULL, int source_line = -1 );

	void createMethodRef(Method* calledMethod);
	void createArrayElemConstants(EiffelType* elemType);

	// ��� ��������� ������, ��� ����� �.�. �������������: ������������ invokespecial ������ invokevirtual
	// noQualify: �������� �������� ������ �� ������
	ByteCode& toByteCode(ByteCode &, bool noQualify);
	ByteCode& toByteCode(ByteCode &bc) {return toByteCode(bc, false); };


	ByteCode& generateCreation(ByteCode &);
	ByteCode& arrayCreation(ByteCode &);

};
