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
	virtual bool canCastTo(const EiffelType* otherType);


	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};