#pragma once
#include "tree_structs.h"
#include "MetaClass.h"

class Feature
{
public:
	Feature(void);
	~Feature(void);

	static bool create(MetaClass* mc, struct NFeature* s);
};

