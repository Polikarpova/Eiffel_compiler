#pragma once
#include "tree_structs.h"

typedef char byte;

class Statement
{

public:

	Statement(void);
	~Statement(void);

	byte* toByteCode();

	static Statement create(struct NStmt* s);
};

