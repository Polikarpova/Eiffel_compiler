#include "MetaClass.h"
#include "Feature.h"

/*static*/ bool MetaClass::create(struct NClass* class_node)
{
	// check name collisions
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
	}
}

bool MetaClass::createFeatures() {

	bool success = false;

	// ÏĞÎÂÅĞÈÒÜ ÷èñëî ğîäèòåëåé è çàïîìíèòü ğîäèòåëÿ
	// ...
	
	struct NFeatureList* List = tree_node->featureList;
	// iterate
	for(struct NFeature* i = List->first ;  ; i = i->next )
	{
		success = Feature::create(this, i);

		if(i == List->last) break;
	}

	return 0;
}