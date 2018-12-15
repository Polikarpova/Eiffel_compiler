#include "LocalVariable.h"


LocalVariable::LocalVariable(void)
{
}

LocalVariable::LocalVariable(QString name, int n, EiffelType* type)
{
	this->name = name.toLower();
	this->n = n;
	this->type = type;
}


LocalVariable::~LocalVariable(void)
{
}


/*static*/ LocalVariable* LocalVariable::create(/*Method* mtd,*/ struct NNameAndType* node, int n)
{
	qDebug("created LocalVariable: %s. it`s N: %s", node->name, n);

	return new LocalVariable(QString(node->name).toLower(),
		n,
		EiffelType::create(node->type)
		);
}
