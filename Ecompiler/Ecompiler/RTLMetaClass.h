#pragma once
#include "MetaClass.h"
#include "EiffelType.h"


class RTLMetaClass : public MetaClass
{

public:
	
	RTLMetaClass(void);
	RTLMetaClass(EiffelProgram* program, const QString& name);
	~RTLMetaClass(void);

	/*methods*/
	virtual const QString& name() { return _name; }
	QString javaPackage() {return QString("rtl");}


	/*fields*/

	//* ������� ��� ������
	QString _name;
};

// ���� �������� ��� RTL-������ ��� ����������� � ���������� ����� ���� ������ RTLMetaClass.h

#include "EiffelNONE.h"
#include "EiffelANY.h"
#include "EiffelSTRING.h"
#include "INTEGER.h"

