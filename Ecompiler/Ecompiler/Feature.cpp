#include "Feature.h"

#include "Method.h"
#include "Field.h"
#include "EiffelClass.h"

Feature::Feature(void)
{
}


Feature::~Feature(void)
{
}

/*static*/ bool Feature::create(MetaClass* mc, struct NFeature* s) {

	//bool success = false;

	QString name(s->name);
	name = name.toLower();

	EiffelProgram* program = EiffelProgram::currentProgram;

	if(isNameConflicting(mc,name))
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

	if( !fe )
		return false;

	// set data which is common for Method & Field
	fe->name = name;
	fe->metaClass = mc;
	fe->recordClients(s->clients);

	return true;
}

bool Feature::isNameConflicting(MetaClass* mc, const QString& lowerName) {
	if( MetaClass::isNameConflicting(lowerName.toUpper()) )
		return true;

	return
		mc->fields.keys().contains(lowerName)
		||
		mc->methods.keys().contains(lowerName);
}

bool Feature::isExportedTo(const QString& upperName)
{
	MetaClass* mc = EiffelProgram::currentProgram -> findClass(upperName);
	return 
		mc && (
			this->clients.contains(upperName) 
			|| this->isExportedTo( mc->getType() )
		);
}
bool Feature::isExportedTo(const EiffelClass* clientClass)
{
	foreach(const QString& clientName , this->clients)
	{
		MetaClass* mc_client_parent = clientClass->metaClass;
		if( mc_client_parent && clientClass->canCastTo(mc_client_parent->getType()) )
		{
			return true;
		}
	}
	return false;
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
