#include "EiffelProgram.h"
#include "MetaClass.h"
#include "RTLMetaClass.h"

/*static*/ EiffelProgram* EiffelProgram::currentProgram = NULL;

EiffelProgram::EiffelProgram(void)
{
}


EiffelProgram::~EiffelProgram(void)
{
	classes.clear();
}


/*static*/ EiffelProgram* EiffelProgram::create(struct NClassList* List, char** syntaxErrors/* = 0*/, int syntaxErrorsN/* = 0*/)
{
	EiffelProgram* program = new EiffelProgram();
	EiffelProgram::currentProgram = program;

	// iterate existing errors
	if(syntaxErrors && syntaxErrorsN)
	{
		for(int i=0 ; i<syntaxErrorsN ; ++i)
		{
			program->logError(QString::fromUtf8("syntax"), QString::fromUtf8(syntaxErrors[i]), -1);
		}
	}

	// ������ 1
	// add RTL classes
	program->createRTL();

	// iterate user classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass::create(i);
		if(i == List->last) break;
	}

	// ������ 2
	program->round2();

	return program;
}

MetaClass* EiffelProgram::findClass(const QString& upperName)
{
	return classes.value(upperName, NULL);
}

bool EiffelProgram::round2()
{
	// QMap<QString, MetaClass*> classes;
	 
	foreach(MetaClass* mc, this->classes)
	{
		mc->createFeatures();
	}

	return true;
}
bool EiffelProgram::round3()
{
	foreach(MetaClass* mc, this->classes)
	{
		mc->round3();
	}

	// set class `NONE` as child of all `leaf`-classes


	return true;
}


void EiffelProgram::createRTL()
{
	MetaClass* mc;

	mc = new EiffelNONE(this);
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;

	mc = new EiffelANY(this);
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;

	mc = new EiffelSTRING(this);
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;

	mc = new RTLMetaClass(this, QString("IO"));
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;
}
