#include "Expression.h"


Expression::Expression(void)
{
}


Expression::~Expression(void)
{
}

/*static*/ Expression* Expression::create(struct NExpr* s) {

	switch(s->type) {
		
		case IntE:
		case RealE:
		case CharE:
		case StringE:
		case BoolE:
			return 0;
		case NotE:
		case UPlusE:
		case UMinusE:
			return 0;
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
			return 0;
		case RefnCallE:
			return 0;
		case PrecursorE:
			return 0;
		case SubscriptE:
			return 0;
		default:
			return 0; //unknow
	}

	return 0;
}