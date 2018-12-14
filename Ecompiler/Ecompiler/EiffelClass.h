#pragma once
#include "EiffelType.h"
//#include <QString>
class MetaClass;

/** ��������� �� ���� �� ������� RTL / ���������������� �������,
	������ ����������� � ���� ��������� / ��������
*/
class EiffelClass : public EiffelType
{

public:
	
	EiffelClass(void);
	EiffelClass(MetaClass* metaClass);
	~EiffelClass(void);

	/** OVERRIDE
		�������� �� ����������� ���������� � ����� ������ ����.
		��������, ��������� ������ �� ����� � ���� ��������� �����.
		�� ��������� ��� �� ����� ���� ������� �� � ����, ����� ���� -- ��������� ����� ��������� ��� ���������.
	*/
	bool canCastTo(const EiffelType* otherType) const;


	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};