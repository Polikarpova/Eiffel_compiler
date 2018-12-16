#include "LocalVariable.h"


LocalVariable::LocalVariable(void)
{
}

LocalVariable::LocalVariable(const QString& name, int n, EiffelType* type)
{
	this->name = name.toLower();
	this->n = n;
	this->type = type;
}
LocalVariable::LocalVariable(EiffelType* type, const QString& name)
{
	this->name = name.toLower();
	this->n = 99;
	this->type = type;
}


LocalVariable::~LocalVariable(void)
{
}


/*static*/ LocalVariable* LocalVariable::create(/*Method* mtd,*/ struct NNameAndType* node, int n)
{
	qDebug("created LocalVariable: %s. it`s N: %d", node->name? node->name : "<null name>", n);

	return new LocalVariable(QString(node->name).toLower(),
		n,
		EiffelType::create(node->type)
		);
}
