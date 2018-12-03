#include "Feature.h"


Feature::Feature(void)
{
}


Feature::~Feature(void)
{
}

Feature* Feature::create(struct NFeature* s) {

	return new Feature();
}