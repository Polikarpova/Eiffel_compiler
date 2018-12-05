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

	QString name(s->name);
	name = name.toLower();

	EiffelProgram* program = EiffelProgram::currentProgram;

	if(program->classes.keys().contains(name))
	{
		program->logError(
			QString("semantic"), 
			QString("Cannot use name %1 for feature of class %2: this name is already in use")
				.arg(name, mc->name()),
			s->loc.first_line);
	
		return false;
	}

	if ( s->routineBody != NULL ) {	
		success = Method::create(mc, s);

	} else {	
		success = Field::create(mc, s);
	}



	return success;
}