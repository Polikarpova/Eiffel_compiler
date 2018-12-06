#include "MetaClass.h"
#include "Feature.h"
#include "Method.h"

MetaClass::MetaClass(EiffelProgram* program, const QString& name)
{
	this->program = program;
	this->parent = NULL;
	this->isAbstract = false;

	JvmConstant jc = { UTF8_VALUE, 0, false };

	// имя класса
	jc.type = UTF8_VALUE;
	jc.value.utf8 = new QString(name);
	this->name_constN = this->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = this->name_constN;
	this->class_constN = this->constantTable.put(jc);
		
}


/*static*/ MetaClass* MetaClass::create(struct NClass* class_node)
{
	// check name collisions
	EiffelProgram* program = EiffelProgram::currentProgram;
	QString name(class_node->className);
	name = name.toUpper();

	if(isNameConflicting(name))
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
		MetaClass* mc = new MetaClass(program, name);
		mc->tree_node = class_node;
		
		if(mc)
			program->classes[ mc->name() ] = mc;

		return mc;
	}
}

Field* MetaClass::findField(const QString& lowerName, bool lookInParents /*= true*/)
{
	Field* p = fields.value(lowerName, NULL);
	if(!p && lookInParents && this->parent)
	{
		this->parent->findField(lowerName);
	}

	return p;
}
/** \return NULL if no class found */
Method* MetaClass::findMethod(const QString& lowerName, bool lookInParents /*= true*/)
{
	return methods.value(lowerName, NULL);
	Method* p = methods.value(lowerName, NULL);
	if(!p && lookInParents && this->parent)
	{
		this->parent->findMethod(lowerName);
	}

	return p;
}


bool MetaClass::createFeatures() {

	bool success = false;

	{
	struct NFeatureList* List = tree_node->featureList;
	// iterate
	if(List) {
		for(struct NFeature* i = List->first ;  ; i = i->next )
		{
			success = Feature::create(this, i);

			if(i == List->last) break;
		}
	}
	}
	
	// Iterate creators list
	{
	// struct NIdList* creationList; // NULL если отсутствует
	struct NIdList* List = tree_node->creationList;
	// iterate
	if(List) {
		for(struct NId* i = List->first ;  ; i = i->next )
		{
			QString name(i->id);
			name = name.toLower();
			
			if( findField(name, false) )
			{
				program->logError(
					QString("semantic"), 
					QString("Cannot use attribute %1 as a constructor of class %2")
						.arg(name, this->name()),
					i->loc.first_line);

				continue;
			}

			Method* mtd_creator = findMethod(name, false);
			if( ! mtd_creator )
			{
				program->logError(
					QString("semantic"), 
					QString("Undefined identifier %1 used as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
					i->loc.first_line);

				continue;
			}

			if( ! mtd_creator->type->isVoid() )
			{
				program->logError(
					QString("semantic"), 
					QString("Cannot use function %1 as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
					i->loc.first_line);

				continue;
			}

			// remember flag: method is creator
			mtd_creator->isCreator = true;

			if(i == List->last) break;
		}
	}
	}

	return 0;
}
bool MetaClass::round3()
{
	/* ПРОВЕРИТЬ число родителей и запомнить родителя (ANY по умолчанию),
	   а также проверить и запомнить переопределения
	struct NInheritFromClassList* List =  tree_node->inheritance;
	int parents_count = 0;
	// iterate
	if(List) {
		for(struct NInheritFromClass* i = List->first ;  ; i = i->next )
		{
			success = Feature::create(this, i);

			if(i == List->last) break;
		}
	}
	// ... */
	
 
	foreach(Method* mtd, this->methods)
	{
		mtd->createBody();
	}

	return true;
}

bool MetaClass::isNameConflicting(const QString& upperName) {
	return EiffelProgram::currentProgram -> findClass(upperName) != NULL;
}

