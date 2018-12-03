#include "EiffelProgram.h"


EiffelProgram::EiffelProgram(void)
{
}


EiffelProgram::~EiffelProgram(void)
{
	classes.clear();
	clients.clear();
}


/*static*/ EiffelProgram* EiffelProgram::create(struct NClassList* List, char** syntaxErrors/* = 0*/, int syntaxErrorsN/* = 0*/)
{
	EiffelProgram* program = new EiffelProgram();

	// iterate errors
	if(syntaxErrors && syntaxErrorsN)
	{
		for(int i=0 ; i<syntaxErrorsN ; ++i)
		{
			CompilerError ce = {QString::fromUtf8("syntax"), QString::fromUtf8(syntaxErrors[i]), -1};
			program->errors.push_back(ce);
		}
	}


	// iterate classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass* meta_class = MetaClass::create(program, i);
		if(meta_class)
			program->classes[ meta_class->name() ] = meta_class;
		if(i == List->last) break;
	}

	return program;
}
