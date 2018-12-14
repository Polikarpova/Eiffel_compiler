#include "Expression.h"
#include "StringExpr.h"
#include "OperationExpr.h"

#include "MetaClass.h"
#include "EiffelClass.h"
#include "Method.h"
#include "LocalVariableRef.h"
#include "FieldRef.h"
#include "ValueMethodCall.h"

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
		if(node->ExprList)
		{
			if(node->ExprList != NULL) {
				EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Call to local variable (`%1`) is not allowed. (Routine: %3.%2)")
						.arg(id, mtd->metaClass->name(), mtd->name),
					node->loc.first_line);
				return NULL;
			}
			else	// единственный вариант для локальной переменой: без аргументов
			{
				// create LocalVariableRef
				return LocalVariableRef::create(mtd, loc_var);
				// finish
			}
		}
		
		// обращение к члену текущего класса
		qualification_class = mtd->metaClass;
	}
	else // Check Qualification as `node->left`
	{
		qualification_expr = Expression::create(mtd, node->left);

		if(qualification_expr == NULL) {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Error occured while analyzing left of `.%1`. (Routine: %3.%2)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
		
		// find out type & class of left expr
		EiffelType* et = qualification_expr->expressionType();

		if( dynamic_cast<EiffelClass*>(et) != nullptr ) {
			qualification_class = ((EiffelClass*)et)->metaClass;
		}
		else {
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Left of `.%1` is not a class (-). (Routine: %3.%2)")
					.arg(id, mtd->metaClass->name(), mtd->name),
				node->loc.first_line);
			return NULL;
		}
	}

	// check if the feature exists if qual. class

	return 0;
}


/*static*/ Expression* Expression::create(Method* mtd, struct NExpr* s) {

	switch(s->type) {
		
		case IntE:
			return 0;
		case RealE:
			return 0;
		case CharE:
			//можно забыть
			return 0;
		case StringE:
			return StringExpr::create(mtd, s);
		case BoolE:
			return 0;
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
			return 0;
		case SubscriptE:
			return 0;
		default:
			return 0; //unknown
	}

	return 0;
}