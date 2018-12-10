#pragma once
#include "MetaClass.h"

class RTLMetaClass : public MetaClass
{

public:
	
	RTLMetaClass(void);
	RTLMetaClass(EiffelProgram* program, const QString& name) 
		: MetaClass(program, name) {};
	~RTLMetaClass(void);

	/*methods*/


	/*fields*/
};

// ���� �������� ��� RTL-������ ��� ����������� � ���������� ����� ���� ������ RTLMetaClass.h

#include "EiffelNONE.h"
#include "EiffelANY.h"
#include "EiffelSTRING.h"

