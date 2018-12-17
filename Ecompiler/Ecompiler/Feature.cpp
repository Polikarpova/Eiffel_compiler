#include "Feature.h"

#include "Method.h"
#include "Field.h"
#include "EiffelClass.h"

Feature::Feature(void)
{
	this->isStatic = false;
}
Feature::Feature(MetaClass* mc, EiffelType* type, const QString& name)
{
	this->tree_node = NULL;
	this->metaClass = mc;
	this->name = name;
	this->type = type;
	this->recordClients(NULL); // set ANY as client
	this->isStatic = false;

	// javaName
	//this->javaName = name;
	this->initJavaName();
}


Feature::~Feature(void)
{
}

void Feature::initJavaName()
{
	this->javaName = name;
	if(javaName == "main")
		javaName = "^" + javaName;
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
	if( ! clientClass->metaClass )
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Cannot get clientClass->metaClass! where: Feature::isExportedTo()"),
			-1);
		return false;
	}

	foreach(const QString& clientName , this->clients)
	{
		MetaClass* metaclass_client = EiffelProgram::currentProgram->findClass(clientName);
		if( ! metaclass_client )
		{
			EiffelProgram::currentProgram->logError(
				QString("internal"), 
				QString("Cannot get find class `%1` in program! where: Feature::isExportedTo()")
					.arg(clientName),
				-1);
			return false;
		}
		bool b = clientClass->canCastTo(metaclass_client->getType());
		if( b )
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

//* создать константы в классе: имя и дескриптор
void Feature::initConstants()
{
	// short int name_constN, descr_constN;

	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	// имя поля/метода
	jc.type = UTF8_VALUE;
	buffer = this->javaName;
	jc.value.utf8 = & buffer;
	this->name_constN = this->metaClass->constantTable.put(jc);
	
	// дескриптор поля/метода
	jc.type = UTF8_VALUE;
	buffer = this->getDescriptor();
	jc.value.utf8 = & buffer;
	this->descr_constN = this->metaClass->constantTable.put(jc);
}
