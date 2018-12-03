#pragma once
#include "EiffelType.h"

class LocalVariable
{

public:

	LocalVariable(void);
	~LocalVariable(void);

	/*fields*/
	short int name_constN;
	int n;
	EiffelType* type;
};

