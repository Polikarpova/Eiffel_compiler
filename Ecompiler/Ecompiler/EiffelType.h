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

	/*fields*/
	struct NType* tree_node;

	/*method*/
	static EiffelType* create(struct NType* type);

	virtual bool isVoid() { return false; }
};

