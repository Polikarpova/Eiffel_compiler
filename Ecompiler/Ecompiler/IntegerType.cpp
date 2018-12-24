#include "IntegerType.h"

/*static*/ IntegerType* IntegerType::singleton = NULL;


IntegerType::~IntegerType(void)
{
}

/*virtual*/ bool IntegerType::canCastTo(const EiffelType* otherType, EiffelType* *convertTo /*= 0*/) const
{
	if(/*convertTo != NULL &&*/ otherType->isReal()) // �������������� � ������������� ����� ����������� (���� ����� ����������� �� ����)
	{
		if(convertTo != NULL) {
			*convertTo = EiffelProgram::currentProgram->findClass("REAL")->getType();
		}
		return true;
	}
	else
	{
		// �������������� �� ���������
		convertTo = 0;
	}

	return otherType->isInteger();
}
