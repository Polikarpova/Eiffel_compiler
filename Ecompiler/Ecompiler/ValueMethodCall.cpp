#include "ValueMethodCall.h"

#include "Method.h"

ValueMethodCall::ValueMethodCall(void)
	: Expression()
{
}


ValueMethodCall::~ValueMethodCall(void)
{
	qDeleteAll(arguments);
	arguments.clear();
}

/*static*/ ValueMethodCall* ValueMethodCall::create(Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification /*= NULL*/ )
{
	int source_line = -1;

	ValueMethodCall* vmc = new ValueMethodCall();

	//Заполнить массив аргументов выражениями
	//arguments << <Expr>*
	struct NExprList* List = argList;
	if(List) {
		for(struct NExpr* i = List->first; i != NULL ; i = i->next) {
			source_line = i->loc.first_line;
			// add expr
			Expression* arg_expr = Expression::create(context_mtd, i);
			if(arg_expr)
				vmc->arguments << arg_expr;

			if(i == List->last) break;
		}
	}

	// проверка соответствия количества аргументов

	int n_formal_args = calledMethod->exactNumberOfArgs();
	int n_actual_args = vmc->arguments.size();

	if( n_actual_args != n_formal_args ) // wrong arg list`s length
	{
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Routine `%1` declares %4 formal parameters, but %5 actual arguments were provided. (In routine: %2.%3)")
				.arg(calledMethod->name, context_mtd->metaClass->name(), context_mtd->name)
				.arg(n_formal_args)
				.arg(n_actual_args),
			source_line);
		delete vmc;
		return NULL;
	}

	// проверка соответствия типов аргументов
	for(int i=0 ; i < n_formal_args; ++i)
	{
		LocalVariable* formal_arg = calledMethod->findLocalVar(i+1); // +1 : 0 is `Current`
		if( !formal_arg )
		{
			EiffelProgram::currentProgram->logError(
				QString("internal"), 
				QString("Cannot find variable # %1 (as parameter) in routine: %2.%3")
					.arg(i)
					.arg(calledMethod->metaClass->name(), calledMethod->name),
				source_line);
			delete vmc;
			return NULL;
		}

		bool types_ok = vmc->arguments[i]->expressionType()->canCastTo( formal_arg->type );
		if(!types_ok)
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Signatures differ in call to routine `%4`.`%1`: cannot convert argument %5 from type `%6` to type `%7`. (In routine: %2.%3)")
					.arg(calledMethod->name, context_mtd->metaClass->name(), context_mtd->name, calledMethod->metaClass->name())
					.arg(i)
					.arg("TODO...","TODO!"),
				source_line);
			delete vmc;
			return NULL;
		}
	}


	vmc->currentMethod = context_mtd;
	vmc->left  = qualification;
	vmc->calledMethod = calledMethod;

	vmc->type = calledMethod->type;

	// report creation
	qDebug("created ValueMethodCall: %s(%d params)", calledMethod->name.data(), n_formal_args);

	return vmc;
}
