#include "Method.h"


Method::Method(void)
{
}


Method::~Method(void)
{
}

/*static*/ Method* Method::create(MetaClass* mc, struct NFeature* node)
{
	/*// check name collisions

	TODO

	EiffelProgram* program = EiffelProgram::currentProgram;
	QString name(class_node->className);
	name = name.toUpper();

	if(program->classes.keys().contains(name))
	{
		program->logError(
			QString("semantic"), 
			QString("Redifiniton of class %1")
				.arg(name),
			class_node->loc.first_line);
	
		return false;
	}
	else
	{
		MetaClass* mc = new MetaClass(program);
		mc->tree_node = class_node;
		
		JvmConstant jc = { UTF8_VALUE, 0, false };

		jc.type = UTF8_VALUE;
		jc.value.utf8 = new QString(name);
		int name_n = mc->constantTable.put(jc);
		
		jc.type = CLASS_N;
		jc.value.class_const = name_n;
		int class_n = mc->constantTable.put(jc);
		
		mc->name_constN  = name_n;
		mc->class_constN = class_n;

		if(mc)
			program->classes[ mc->name() ] = mc;

		return true;
	}*/

	

	return NULL;
}