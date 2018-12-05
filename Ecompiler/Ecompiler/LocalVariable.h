#pragma once
#include "EiffelType.h"
#include <qstring.h>

class LocalVariable
{

public:

	LocalVariable(void);
	~LocalVariable(void);

	/*fields*/
	QString name;
	int n;
	EiffelType* type;
};
