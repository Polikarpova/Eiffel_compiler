#pragma once
#include "EiffelType.h"
#include "MetaClass.h"

/** ��������� �� ���� �� ������� RTL / ���������������� �������,
	������ ����������� � ���� ��������� / ��������
*/
class EiffelClass : public EiffelType
{

public:
	
	EiffelClass(void);
	~EiffelClass(void);

	/*fields*/
	MetaClass* metaClass;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};