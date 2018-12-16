#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

Method::Method(void)
{
	this->isCreator = false;
}
Method::Method(MetaClass* mc, EiffelType* type, const QString& name, QList<LocalVariable> argList /*= QList<>()*/ )
	: Feature(mc, type, name)
{
	this->isCreator = false;

	// local vars
	int loc_i = 0;

	// 1 (Current)
	LocalVariable* lvr = new LocalVariable("current", loc_i, mc->getType() );
	this->localVariables[lvr->name] = lvr;
	++loc_i;

	// + формальные параметры
	if( ! argList.isEmpty() )
	{
		foreach(LocalVariable lvar, argList ) {
			// add var
			this->localVariables[lvar.name] = new LocalVariable(lvar.name, loc_i, lvar.type );
			++loc_i;
		}
	}

	// «афиксировать количество параметров
	this->paramCount = loc_i;
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

	// «афиксировать количество параметров
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
	if( ! mtd->type )
	{
		qDebug("Method does not declared with a type! where: Method::create()");
		delete mtd;
		return false;
	}

	mtd->descriptor = mtd->createDescriptor();

	// report creation
	qDebug("created Method: %s. Descriptor: %s", node->name, mtd->getDescriptor().toLocal8Bit().data());

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


QString Method::createDescriptor() {

	QString result = "(";

	//пройтись по всем параметрам
	for(int i=1 ; i<this->paramCount ; ++i )
	{
		result += this->findLocalVar(i)->type->descriptor();
	}

	result += ")";

	//добавить дескриптор возвращаемого значени€
	result += this->type->descriptor();

	return result;
}

/*
QString Method::getTypeDescriptor(EiffelType* type)
{
	QString result;

	//EiffelClass* ec;
	//EiffelArray* ea;

	//switch(type->tree_node->type) {
	//
	//	case VoidV:
	//		result += "V";
	//		return result;
	//	case ClassV:
	//		result += "L" + ec->className + ";";
	//		return result;
	//	case ArrayV:
	//		result += "[";
	//		this->getTypeDescriptor(ea->elementType);
	//		return result;
	//	case IntegerV:
	//		result += "I";
	//		return result;
	//	case RealV:
	//		result += "D";
	//		return result;
	//	case CharacterV:
	//		result += "C";
	//		return result;
	//	case StringV:
	//		result += "Ljava/lang/String;";
	//		return result;
	//	case BooleanV:
	//		result += "Z";	//true or false
	//		return result;
	//	default:
	//		result += "<unknownType!>";	//unknown
	//		return result;
	//}
	return result;
} // */

bool Method::checkArguments(const QList<Expression*>& factParams) {

	return false;
}
