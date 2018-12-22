#include "LocalVariable.h"


LocalVariable::LocalVariable(void)
{
}

LocalVariable::LocalVariable(const QString& name, int n, EiffelType* type)
{
	this->name = name.toLower();
	this->n = n;
	this->type = type;
	//qDebug("created new LocalVariable: `%s`. N: %d. Type: %s", this->name.toLocal8Bit().data(), n, type->descriptor().toLocal8Bit().data());
}
LocalVariable::LocalVariable(EiffelType* type, const QString& name)
{
	this->name = name.toLower();
	this->n = 99;
	this->type = type;
	//qDebug("created new LocalVariable: `%s`. Type: %s", this->name.toLocal8Bit().data(), type->descriptor().toLocal8Bit().data());
}


LocalVariable::~LocalVariable(void)
{
}


/*static*/ LocalVariable* LocalVariable::create(/*Method* mtd,*/ struct NNameAndType* node, int n)
{
	qDebug("created LocalVariable: %s. No: %d. Source: tree node", node->name? node->name : "<null name>", n);

	return new LocalVariable(QString(node->name).toLower(),
		n,
		EiffelType::create(node->type)
		);
}
