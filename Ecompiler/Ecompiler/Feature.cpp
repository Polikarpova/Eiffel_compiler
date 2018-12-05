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

	Feature* fe;
	if ( s->routineBody != NULL ) {	
		fe = Method::create(mc, s);

	} else {	
		fe = Field::create(mc, s);
	}

	// set data which is common for Method & Field
	fe->name = name;
	fe->recordClients(s->clients);

	fe->descriptor = fe->createDescriptor();

	return success;
}

void Feature::recordClients(const struct NIdList* List) {

	if ( List == NULL ) {
	
		this->clients.insert("ANY");
	} else {
	
		for(struct NId* i = List->first; ; i = i->next) {
		
			this->clients.insert( QString(i->id).toUpper() );

			if(i == List->last) break;
		}
	}
}