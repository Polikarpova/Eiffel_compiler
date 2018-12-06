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
	EiffelClass(MetaClass* metaClass) {
		this->tree_node = NULL;
		this->metaClass = metaClass;
		this->className = this->metaClass->name();
	}
	~EiffelClass(void);

	/*fields*/
	MetaClass* metaClass;

	QString className;

	/*methods*/
	static EiffelClass* create(struct NType* type);
};