#include "ValueMethodCall.h"

#include "Method.h"

ValueMethodCall::ValueMethodCall(void)
{
}


ValueMethodCall::~ValueMethodCall(void)
{
	arguments.clear();
}

/*static*/ ValueMethodCall* ValueMethodCall::create(Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification /*= NULL*/ )
{
	// проверка соответствия количества и типов аргументов

	//arguments << <Expr>*
	struct NExprList* List = argList;
	if(List) {
		for(struct NExpr* i = List->first; ; i = i->next) {
			// add expr
			//LocalVariable* lvr = LocalVariable::create(i, loc_i);
			//mtd->localVariables[lvr->name] = lvr;
			//++loc_i;

			if(i == List->last) break;
		}
	}

	int n_args = calledMethod->exactNumberOfArgs();
	

	ValueMethodCall* vmc = new ValueMethodCall();
	vmc->currentMethod = context_mtd;
	vmc->left  = qualification;
	vmc->calledMethod = calledMethod;

	vmc->type = calledMethod->type;

	return vmc;
}
