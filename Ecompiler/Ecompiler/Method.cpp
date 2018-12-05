#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Method::Method(void)
{
	this->isCreator = false;
	this->isRedefined = false;
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

	QString name(node->name);
	name = name.toLower();

	Method* mtd = new Method();
	// add to class
	mc->methods[name] = mtd;

	// local vars
	int loc_i = 0;

	// 1 (Current)
	// заглушка NULL
	LocalVariable* lvr = new LocalVariable("Current", loc_i , NULL /*!!! EiffelType::create(???)*/ );
	mtd->localVariables[lvr->name] = lvr;
	++loc_i;

	// + формальные параметры
	struct NNameAndTypeList* List;
	List = node->params;
	if(List) {
		for(struct NNameAndType* i = List->first; ; i = i->next) {
			// add var
			LocalVariable* lvr = LocalVariable::create(i, loc_i);
			mtd->localVariables[lvr->name] = lvr;
			++loc_i;

			if(i == List->last) break;
		}
	}

	// Зафиксировать количество параметров
	mtd->paramCount = loc_i;

	// + локальные переменные
	List = node->localVars;
	if(List) {
		for(struct NNameAndType* i = List->first; ; i = i->next) {
			// add var
			LocalVariable* lvr = LocalVariable::create(i, loc_i);
			mtd->localVariables[lvr->name] = lvr;
			++loc_i;

			if(i == List->last) break;
		}
	}

	mtd->tree_node = node;
	mtd->type = EiffelType::create(node->type);
	mtd->descriptor = mtd->createDescriptor(mtd->type);

	return mtd;
}

QString Method::createDescriptor(EiffelType* type) {

	QString result = "(";

	//пройтись по всем параметрам
	if ( this->tree_node->params != NULL )
	for(NNameAndType* i = this->tree_node->params->first; ; i = i->next) {
	
		EiffelType* et = EiffelType::create(i->type);
		result += this->getTypeDescriptor(et);
	}

	result += ")";

	//добавить дескриптор возвращаемого значения
	result += this->getTypeDescriptor(type);

	return result;
}

QString Method::getTypeDescriptor(EiffelType* type)
{
	QString result;

	EiffelClass* ec;
	EiffelArray* ea;

	switch(type->tree_node->type) {
	
		case VoidV:
			result += "V";
			return result;
		case ClassV:
			/* EiffelClass* */ ec = (EiffelClass*)type;
			result += "L" + ec->className + ";";
			return result;
		case ArrayV:
			result += "[";
			/* EiffelArray* */ ea = (EiffelArray*)type;
			this->getTypeDescriptor(ea->elementType);
			return result;
		case IntegerV:
			result += "I";
			return result;
		case RealV:
			result += "D";
			return result;
		case CharacterV:
			result += "C";
			return result;
		case StringV:
			result += "Ljava/lang/String;";
			return result;
		case BooleanV:
			result += "Z";	//true or false
			return result;
		default:
			result += "<unknownType!>";	//unknown
			return result;
	}
}