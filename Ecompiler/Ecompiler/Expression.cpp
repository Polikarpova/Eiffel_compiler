#include "Expression.h"

#include "IntExpr.h"
#include "StringExpr.h"
#include "BoolExpr.h"
#include "OperationExpr.h"
#include "CharExpr.h"
#include "RealExpr.h"

#include "MetaClass.h"
#include "EiffelClass.h"
#include "Method.h"
#include "LocalVariableRef.h"
#include "FieldRef.h"
#include "ArrayElemRef.h"
#include "MethodCall.h"

Expression::Expression(void)
{
	this->currentMethod = 0;
	this->tree_node = 0;
	this->_isLeftValue = false;
	this->left = 0;
	this->right = 0;
	this->type = 0;
}


Expression::~Expression(void)
{
}

/** mtd - метод, где всё происходит
*/
Expression* fromRefnCall(Method* mtd, struct NExpr* node)
{
	if(!node)
		return 0;

	QString id(node->value.id);
	id = id.toLower();

	Expression* qualification_expr = 0;
	MetaClass* qualification_class = 0;

	if(node->left == NULL)	// единственный вариант для локальной переменой: без квалификации
	{
		LocalVariable* loc_var = mtd->findLocalVar(id);
		if(loc_var)
		{
			if(node->ExprList != NULL) {
				EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Call to local variable (`%1`) is not allowed. (In routine: %2.%3)")
						.arg(id, mtd->metaClass->name(), mtd->name),
					node->loc.first_line);
				return NULL;
			}
			else	// единственный вариант для локальной переменой: без аргументов
			{
				// create LocalVariableRef
				LocalVariableRef* lvr = LocalVariableRef::create(mtd, loc_var);
				if(lvr)  lvr->tree_node = node;
				return lvr;
				// finish
			}
		}
		
		// обращение к члену текущего класса (неявный Current)
		qualification_class = mtd->metaClass;
	}
	else // Check Qualification as `node->left`
	{
		qualification_expr = Expression::create(mtd, node->left);

		if(qualification_expr == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Error occured while analyzing left of `.%1`. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		
		// find out type & class of left expr
		EiffelType* et = qualification_expr->expressionType();

		if( dynamic_cast<EiffelClass*>(et) != nullptr ) {
			qualification_class = ((EiffelClass*) et)->metaClass;
		}
		else {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Left of `.%1` is not an object (cannot call anything on it). (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
	}

	// check if the feature exists if qualification_class class

	Feature* called_feature = qualification_class->findFeature(id);

	if(called_feature == NULL) {
		if(node->left == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Using undefined local variable or feature `%1`. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
		} else {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Using undefined feature `%1` of class `%4`. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name, qualification_class->name()),
				node->loc.first_line);
		}
		return NULL;
	}

	if( ! called_feature->isExportedTo(mtd->metaClass) ) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Cannot use feature `%1` declared in class `%4`: it is not exported to class `%2`. (In routine: %2.%3)")
				.arg(id, mtd->metaClass->name(), mtd->name, called_feature->metaClass->name()),
			node->loc.first_line);
		return NULL;
	}

	if( called_feature->isField() ) // feature is a field
	{
		if(node->ExprList != NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Calling to field (`%1`) is not allowed. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		else	// единственный вариант для поля: без аргументов
		{
			// create FieldRef. Parameters: (Method* mtd, Field* field, Expression* qualification = NULL );
			FieldRef* fr = FieldRef::create(mtd, (Field*)called_feature, qualification_expr);
			if(fr)  fr->tree_node = node;
			return fr;
			// finish
		}
	}

	if( called_feature->isMethod() ) // feature is a method
	{
		if( called_feature->isVoid() ) // Void method
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Invalid function call: routine `%1` is a procedure, function expected. (In routine: %2.%3)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		else
		{
			// create MethodCall. Parameters: (Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification /*= NULL*/ )
			MethodCall* mtdc = MethodCall::create(mtd, (Method*)called_feature, node->ExprList, qualification_expr);
			if(mtdc)  mtdc->tree_node = node;
			return mtdc;
			// finish
		}
	}
	else
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Cannot identify feature `%1` of class `%4` as neither attribute nor function. (In routine: %2.%3)")
				.arg(id, mtd->metaClass->name(), mtd->name, qualification_class->name()),
			node->loc.first_line);
		return NULL;
	}

	return NULL;
}

MethodCall* fromPrecursor(Method* mtd, struct NExpr* node)
{
	if(!node)
		return 0;
	
	if(node->left != NULL) {	//  квалификация не нужна для PRECURSOR
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Extra qualification for `PRECURSOR` structure. (In routine %2.%1)")
				.arg(mtd->name, mtd->metaClass->name()),
			node->loc.first_line);
				
		return NULL;
	}


	MetaClass* base_class = 0;

	if(node->value.id) {

		QString className(node->value.id);
		className = className.toLower();

		base_class = EiffelProgram::currentProgram->findClass(className);

		if(base_class == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Undefined class `%1` in `PRECURSOR{ %1 }` (In routine %3.%2)")
					.arg(node->value.id, mtd->name, mtd->metaClass->name()),
				node->loc.first_line);
				
			return NULL;
		}

		if( ! mtd->metaClass->getType()->canCastTo( base_class->getType() ) ) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Cannot use class `%1` in `PRECURSOR{ %1 }` within routine `%3.%2`: `%1` is not an ancestor of `%3`.")
					.arg(node->value.id, mtd->name, mtd->metaClass->name()),
				node->loc.first_line);
				
			return NULL;
		}
	} else { // (empty id) PRECURSOR without { }
		
		base_class = mtd->metaClass->parent;

		if(base_class == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("internal"), 
				QString("Class `%2` does`nt have direct parent! ( `PRECURSOR{ %1 }` in routine %2.%1)")
					.arg(mtd->name, mtd->metaClass->name()),
				node->loc.first_line);
				
			return NULL;
		}
	}

	// поиск наследуемого метода
	Feature* base_feature = base_class->findFeature(mtd->name);

	if( ! base_feature->isMethod() ) {
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Feature of class `$3` accessed by `PRECURSOR` structure is not a routine. (In routine %2.%1)")
				.arg(mtd->name, mtd->metaClass->name(), base_class->name()),
			node->loc.first_line);
				
		return NULL;
	}

	// create & finish
	MethodCall* mtdc = MethodCall::create(mtd, (Method*)base_feature, node->ExprList, NULL/*qualification*/);
	if(mtdc)  mtdc->tree_node = node;
	return mtdc;
}

/*static*/ Expression* Expression::create(Method* mtd, struct NExpr* s) {

	switch(s->type) {
		
		case IntE:
			return IntExpr::create(mtd, s);
		case RealE:
			return RealExpr::create(mtd, s);
		case CharE:
			return CharExpr::create(mtd, s);
		case StringE:
			return StringExpr::create(mtd, s);
		case BoolE:
			return BoolExpr::create(mtd, s);
		case NotE:
		case UPlusE:
		case UMinusE:
		case PowerE:
		case MulE:
		case DivE:
		case PlusE:
		case MinusE:
		case EqualsE:
		case NotEqualE:
		case LessE:
		case GreaterE:
		case LessOrEqualE:
		case GreaterOrEqualE:
		case AndE:
		case AndThenE:
		case OrE:
		case OrElseE:
		case XORE:
		case ImpliesE:
			return OperationExpr::create(mtd, s);
		case RefnCallE:
			return fromRefnCall(mtd, s);
		case PrecursorE:
			return fromPrecursor(mtd, s);
		case SubscriptE:
			return ArrayElemRef::create(mtd, s);
		default:
			return 0; //unknown
	}

	return 0;
}

EiffelType* Expression::expressionType()
{
	return getReturnType();
}

EiffelType* Expression::getReturnType() {

	//простые выражения, которые имеют тип IntE, RealE, CharE, StringE, BoolE уже знают о своём типе. Он записывается в их конструкторе
	//так же если ранее это функция вызывалась для текущего объекта, то он уже знает о своём типе и нет надобности опять его высчитывать
	if( type == NULL ) {

		//рекурсивное узнавание типа и его запоминание?
		switch(tree_node->type) {
			case NotE:
			case UPlusE:
			case UMinusE:
			case PowerE:
			case MulE:
			case DivE:
			case PlusE:
			case MinusE:
			case EqualsE:
			case NotEqualE:
			case LessE:
			case GreaterE:
			case LessOrEqualE:
			case GreaterOrEqualE:
			case AndE:
			case AndThenE:
			case OrE:
			case OrElseE:
			case XORE:
			case ImpliesE:
				{
				OperationExpr* oe = (OperationExpr*) this;
				type = oe->getReturnType();
				}
				break;
			default:
				type = NULL;
				break; //unknown
		}
	}
	
	return type;
}