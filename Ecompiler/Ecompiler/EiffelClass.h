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
		�������� �� ����������� ���������� �������� ������ � ����� ������ ������.
		���������� ��������, ���� otherType - �����, ������ ���������� ��� ������� ��� �������� ����������� otherType.
	*/
	bool canCastTo(const EiffelType* otherType, EiffelType* *convertTo = 0) const;


	/*fields*/
	MetaClass* metaClass;

	const QString& className() const;
	virtual bool isReference() const { return true; }
	virtual bool isClass()     const { return true; }
	//* ���������� ������ � ������ �������������: `L�����.�����;`
	virtual QString descriptor();
	virtual QString toReadableString() const {return this->className();};

	/*methods*/
	static EiffelClass* create(struct NType* type);
};