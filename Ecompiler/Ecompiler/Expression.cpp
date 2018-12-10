#include "Expression.h"
#include "StringExpr.h"
#include "OperationExpr.h"

Expression::Expression(void)
{
}


Expression::~Expression(void)
{
}

/*static*/ Expression* Expression::create(Method* mtd, struct NExpr* s) {

	switch(s->type) {
		
		case IntE:
			return 0;
		case RealE:
			return 0;
		case CharE:
			//����� ������
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
			return 0;
		case PrecursorE:
			return 0;
		case SubscriptE:
			return 0;
		default:
			return 0; //unknown
	}

	return 0;
}