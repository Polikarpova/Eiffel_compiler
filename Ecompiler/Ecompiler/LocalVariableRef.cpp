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

///*static*/ LocalVariableRef* LocalVariableRef::createRtlClassRef(Method* mtd, const QString& uncasedName)
//{
//	MetaClass* static_class = EiffelProgram::findClass( uncasedName.toUpper() );
//
//	if(static_class && static_class->isStatic)
//	{
//		LocalVariableRef* lvr = new LocalVariableRef();
//		lvr->currentMethod = mtd;
//		lvr->locVar = 0;
//		// ! lvr->type = locVar->type;
//		return lvr;
//		
//	}
//
//	return 0;
//}
