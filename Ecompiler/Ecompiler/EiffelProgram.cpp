#include "EiffelProgram.h"
#include "MetaClass.h"

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

	// iterate errors
	if(syntaxErrors && syntaxErrorsN)
	{
		for(int i=0 ; i<syntaxErrorsN ; ++i)
		{
			program->logError(QString::fromUtf8("syntax"), QString::fromUtf8(syntaxErrors[i]), -1);
		}
	}


	// iterate classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass* meta_class = MetaClass::create(i);
		if(meta_class)
			program->classes[ meta_class->name() ] = meta_class;
		if(i == List->last) break;
	}

	return program;
}
