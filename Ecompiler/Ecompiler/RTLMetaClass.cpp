#include "RTLMetaClass.h"


RTLMetaClass::RTLMetaClass(void)
{
}
RTLMetaClass::RTLMetaClass(EiffelProgram* program, const QString& name) {
	this->program = program;
	this->parent = NULL;		// �����! �������� �� ������� (���� ����� �� ��� �� �����)
	this->isAbstract = false;
	this->_exprType = NULL;
	this->tree_node = NULL;

	this->_name = name;
};


RTLMetaClass::~RTLMetaClass(void)
{
}
