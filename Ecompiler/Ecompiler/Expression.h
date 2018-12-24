#pragma once
#include "TreeNode.h"
#include "EiffelType.h"
#include "ByteCode.h"

class Method;

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	//* �����-��������
	Method* currentMethod;

	/*methods*/
	static Expression* create(Method* mtd, struct NExpr* s);
	
	//������������� � �������� �������
	virtual bool isLeftValue() { return this->_isLeftValue; };
	
	/** ������ �������� ������ �� �����.
		���� ��������� �� ��������� �����
		�������, ������� false.
	*/
	virtual bool setRightValue(Expression* r, bool force = false) { return false; };

	//���������
	//���������� ��� ������������ ����������
	//2+2 ������ INTEGER
	EiffelType* expressionType();

	/*fields*/
	struct NExpr* tree_node;

	bool _isLeftValue;
	bool castI2F;

	Expression* left;
	Expression* right;
	EiffelType* type;	//��� ������������� ��������

	virtual ByteCode& toByteCode(ByteCode &bc) {return bc.log("/!\\ expr -> code not implemented!.."); };

	ByteCode& applyI2F(ByteCode &bc);


private:
	EiffelType* getReturnType();
};