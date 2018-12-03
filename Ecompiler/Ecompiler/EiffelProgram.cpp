#include "EiffelProgram.h"


EiffelProgram::EiffelProgram(void)
{
}


EiffelProgram::~EiffelProgram(void)
{
	classes.clear();
	clients.clear();
}


/*static*/ EiffelProgram* EiffelProgram::create(struct NClassList* List)
{
	EiffelProgram* program = new EiffelProgram();

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
