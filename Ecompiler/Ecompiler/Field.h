#pragma once
#include "Feature.h"
#include "EiffelType.h"
#include "qset.h"

class Field : public Feature
{

public:

	Field(void);
	~Field(void);

	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* node);
};

