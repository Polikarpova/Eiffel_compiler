#pragma once
#include "tree_structs.h"

class Feature
{
public:
	Feature(void);
	~Feature(void);

	static Feature* create(struct NFeature* s);
};

