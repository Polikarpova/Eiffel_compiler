#include "MetaClass.h"
#include "Feature.h"
#include "Method.h"
#include "Field.h"

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
		p = this->parent->findField(lowerName, lookInParents);
	}

	return p;
}
Method* MetaClass::findMethod(const QString& lowerName, bool lookInParents /*= true*/)
{
	Method* p = methods.value(lowerName, NULL);
	if(!p && lookInParents && this->parent)
	{
		p = this->parent->findMethod(lowerName, lookInParents);
	}

	return p;
}
Feature* MetaClass::findFeature(const QString& lowerName, bool lookInParents /*= true*/)
{
	Feature* p = findMethod(lowerName, false);
	if(!p)
	{
		p = findField(lowerName, false);
	}
	if(!p && lookInParents && this->parent)
	{
		p = this->parent->findFeature(lowerName, lookInParents);
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

				break;
			}
			else
			{
				Method* mtd_creator = findMethod(name, false);
				if( ! mtd_creator )
				{
					program->logError(
						QString("semantic"), 
						QString("Undefined identifier %1 used as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
						i->loc.first_line);
				}
				else if( ! mtd_creator->type->isVoid() )
				{
					program->logError(
						QString("semantic"), 
						QString("Cannot use function %1 as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
						i->loc.first_line);
				} 
				else
				{
					// remember flag: method is creator
					mtd_creator->isCreator = true;
					success = true;
				}
			}
			if(i == List->last) break;
		}
	}
	}

	return success;
}
bool MetaClass::round3()
{
	/* ПРОВЕРИТЬ число родителей и запомнить родителя (ANY по умолчанию),
	   а также проверить и запомнить переопределения */
	this->parent = NULL;

	struct NInheritFromClassList* List =  tree_node->inheritance;
	// iterate
	if(List) {
		for(struct NInheritFromClass* i = List->first ;  ; i = i->next )
		{
			if(this->parent != NULL) {
				program->logError(
					QString("semantic"), 
					QString("Declaring multiple parents for class `%1`; this feature of Eiffel language is not supported")
						.arg(this->name()),
					i->loc.first_line);
				
				continue;
			}

			if( !createInheritance(i) )
			{
				continue;
			}

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

bool MetaClass::createInheritance(struct NInheritFromClass* node)
{
	QString name(node->className);
	name = name.toUpper();
	// предок
	MetaClass* ancestor = program->findClass(name);

	if(ancestor == NULL) {
		program->logError(
			QString("semantic"), 
			QString("Undefined class `%1` is used as parent of class %2")
				.arg(node->className, this->name()),
			node->loc.first_line);
				
		return false;
	}
	
	this->parent = ancestor;
	
	struct NIdList* List =  node->redefineList;
	// iterate
	if(List) {
		for(struct NId* i = List->first ;  ; i = i->next )
		{
			QString name(i->id);
			name = name.toLower();

			if( ! this->parent->findFeature(name, true) )
			{
				program->logError(
					QString("semantic"), 
					QString("Redefine subclause `%1` does not denote redefined feature of class %2; parent %3 does not have such feature")
						.arg(name, this->name(), this->parent->name()),
					i->loc.first_line);

				return false;
			}


			if(i == List->last) break;
		}
	}
	return true;
}

bool MetaClass::isNameConflicting(const QString& upperName) {
	return EiffelProgram::currentProgram -> findClass(upperName) != NULL;
}
