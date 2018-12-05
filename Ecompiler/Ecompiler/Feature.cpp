#include "Feature.h"

#include "Method.h"
#include "Field.h"

Feature::Feature(void)
{
}


Feature::~Feature(void)
{
}

/*static*/ bool Feature::create(MetaClass* mc, struct NFeature* s) {

	bool success = false;

	if ( s->routineBody != NULL ) {	
		success = Method::create(mc, s);
	} else {	
		success = Field::create(mc, s);
	}

	return success;
}