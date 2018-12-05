#pragma once
#include "EiffelType.h"
#include <qstring.h>
#include "tree_structs.h"

class Method;

class LocalVariable
{

public:
	
	LocalVariable(void);
	LocalVariable(QString name, int n, EiffelType* type);
	~LocalVariable(void);

	/*fields*/
	QString name;
	int n;
	EiffelType* type;

	static LocalVariable* create(struct NNameAndType* node, int n);
};
