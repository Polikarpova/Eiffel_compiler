#include "MetaClass.h"


/*static*/ MetaClass* MetaClass::create(/*EiffelProgram* program,*/ struct NClass* class_node)
{
	// check name collisions
	EiffelProgram* program = EiffelProgram::currentProgram;
	QString name(class_node->className);
	
	if(program->classes.keys().contains(name))
	{
		program->logError(
			QString("semantic"), 
			QString("Redifiniton of class %1")
				.arg(name),
			class_node->loc.first_line);
	
		return NULL;
	}
	else
	{
		MetaClass* mc = new MetaClass(program);
		
		JvmConstant jc = { UTF8_VALUE, 0, false };

		jc.type = UTF8_VALUE;
		jc.value.utf8 = &name;
		int name_n = mc->constantTable.put(jc);
		
		jc.type = CLASS_N;
		jc.value.class_const = name_n;
		int class_n = mc->constantTable.put(jc);
		
		mc->name_constN  = name_n;
		mc->class_constN = class_n;

		return mc;
	}
}
