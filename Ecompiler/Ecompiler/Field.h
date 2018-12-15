#pragma once
#include "Feature.h"
#include "EiffelType.h"
#include "qset.h"

class Field : public Feature
{

public:

	Field(void);
	~Field(void);

	virtual bool isMethod() { return false;}
	virtual bool isField()  { return true; }

	/*methods*/
	static Field* create(MetaClass* mc, struct NFeature* node);

	QString createDescriptor();
};

