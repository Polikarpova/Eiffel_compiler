#include "Method.h"
#include "EiffelClass.h"

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

	return NULL;
}

QString Method::createDescriptor() {

	QString result = "(";

	//пройтись по всем параметрам

	//switch(this->type->tree_node->type) {
	//
	//	case VoidV:
	//		//Выдать ошибку?
	//		break;
	//	case ClassV:
	//		EiffelClass* ec = (EiffelClass*)this->type;
	//		result += "L" + ec->className + ";";
	//		break;
	//	case ArrayV:
	//		result += "[";
	//		break;
	//	case IntegerV:
	//		result += "I";
	//		break;
	//	case RealV:
	//		result += "D";
	//		break;
	//	case CharacterV:
	//		result += "C";
	//		break;
	//	case StringV:
	//		result += "Ljava/lang/String;";
	//		break;
	//	case BooleanV:
	//		result += "Z";	//true or false
	//		break;
	//}
	

	result += ")";

	//добавить дескриптор возвращаемого значения

	return result;
}
