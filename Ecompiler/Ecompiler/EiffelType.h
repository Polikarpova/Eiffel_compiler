#pragma once
#include "tree_structs.h"
#include "EiffelProgram.h"


/** ����� ���, ����������� � ���� ��������� / ��������.
	���� ����� �����, ��� ����� ��������� ����-��� ��� ������� �����������,
	������������ � ������ Java.
*/
class EiffelType
{

public:

	EiffelType(void);
	~EiffelType(void);

	/*fields*/
	struct NType* tree_node;

	/*method*/
	static EiffelType* create(struct NType* type);

	virtual bool isVoid() const { return false; }
	virtual bool isReference() const { return false; }
	virtual bool isClass() const { return false; }
	virtual bool isString() const { return false; }
	virtual bool isArray() const { return false; }
	virtual bool isInteger() const { return false; }
	virtual bool isReal() const { return false; }
	virtual bool isBoolean() const { return false; }

	/** �������� �� ����������� ���������� � ����� ������ ����.
		��������, ��������� ������ �� ����� � ���� ��������� �����.
		�� ��������� ��� �� ����� ���� ������� �� � ����, ����� ���� -- ��������� ����� ��������� ��� ���������.
	*/
	virtual bool canCastTo(const EiffelType* otherType) const;

	virtual QString descriptor() {return QString("<!Type!>");}
	
	virtual QString toReadableString() const {return "Child type did not implemented type helper...";};
};

