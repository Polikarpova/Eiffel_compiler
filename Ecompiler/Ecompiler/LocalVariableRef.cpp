#include "LocalVariableRef.h"
#include "LocalVariable.h"


LocalVariableRef::LocalVariableRef(void)
	: Expression()
{
	this->locVar = 0;
}


LocalVariableRef::~LocalVariableRef(void)
{
}

/*static*/ LocalVariableRef* LocalVariableRef::create(Method* mtd, LocalVariable* locVar) {
	LocalVariableRef* lvr = new LocalVariableRef();
	lvr->currentMethod = mtd;
	lvr->locVar = locVar;
	lvr->type = locVar->type;
	return lvr;
}
