#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Method::Method(void)
{
	this->isCreator = false;
	//this->isRedefined = false;
}


Method::~Method(void)
{
}

/*static*/ Method* Method::create(MetaClass* mc, struct NFeature* node)
{
	QString name(node->name);
	name = name.toLower();

	Method* mtd = new Method();
	// add to class
	mc->methods[name] = mtd;

	// local vars
	int loc_i = 0;

	// 1 (Current)
	// заглушка NULL
	LocalVariable* lvr = new LocalVariable("current", loc_i, mc->getType() );
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

bool Method::createBody()
{
	this->body.currentMethod = this;
	return 
		this->body.createBody(this->tree_node->routineBody);
}

LocalVariable* Method::findLocalVar(const QString& lowerName)
{
	return this->localVariables.value(lowerName, NULL);
}

LocalVariable* Method::findLocalVar(int n)
{
	foreach(LocalVariable* lvar , this->localVariables)
	{
		if(lvar->n == n)
			return lvar;
	}
	return NULL;
}


QString Method::createDescriptor(EiffelType* type) {

	QString result = "(";


	if(this->tree_node->params != NULL) {
		//пройтись по всем параметрам
		for(NNameAndType* i = this->tree_node->params->first; ; i = i->next) {
	
			EiffelType* et = EiffelType::create(i->type);
			result += this->getTypeDescriptor(et);
			delete et;
		}
	}

	result += ")";

	//добавить дескриптор возвращаемого значения

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

bool Method::checkArguments(const QList<Expression*>& factParams) {

	return false;
}
