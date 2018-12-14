#include "ValueMethodCall.h"

#include "Method.h"

ValueMethodCall::ValueMethodCall(void)
{
}


ValueMethodCall::~ValueMethodCall(void)
{
	arguments.clear();
}

/*static*/ ValueMethodCall* ValueMethodCall::create(Method* context_mtd, Method* calledMethod, struct NExprList* List, Expression* qualification /*= NULL*/ )
{
	// проверка соответствия количества и типов аргументов

	//arguments << <Expr>*

	ValueMethodCall* vmc = new ValueMethodCall();
	vmc->currentMethod = context_mtd;
	vmc->left  = qualification;
	vmc->calledMethod = calledMethod;

	vmc->type = calledMethod->type;

	return vmc;
}
