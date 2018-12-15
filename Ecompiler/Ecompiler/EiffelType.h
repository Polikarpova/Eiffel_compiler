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

	/** �������� �� ����������� ���������� � ����� ������ ����.
		��������, ��������� ������ �� ����� � ���� ��������� �����.
		�� ��������� ��� �� ����� ���� ������� �� � ����, ����� ���� -- ��������� ����� ��������� ��� ���������.
	*/
	virtual bool canCastTo(const EiffelType* otherType) const;

	virtual QString javaPackage() {return QString("eiffel");}

	virtual QString descriptor() {return QString("<!>");}
	
	virtual QString toReadableString() const {return "not implemented yet...";};
};

