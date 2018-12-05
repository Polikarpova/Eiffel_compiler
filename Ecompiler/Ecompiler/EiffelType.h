#pragma once
#include "tree_structs.h"

/** ����� ���, ����������� � ���� ��������� / ��������.
	���� ����� �����, ��� ����� ��������� ����-��� ��� ������� �����������,
	������������ � ������ Java.
*/
class EiffelType
{

public:

	EiffelType(void);
	~EiffelType(void);

	/*method*/
	static EiffelType* create(struct NType* type);

	virtual bool isVoid() { return false; }
};

