#pragma once
#include "Expression.h"
#include "QList"

class Method;

class ValueMethodCall : public Expression
{

public:
	ValueMethodCall(void);
	~ValueMethodCall(void);

	/*fields*/

	short int methodref_constN;

	//* метод, к которому производится доступ
	Method* calledMethod;

	//* список аргументов метода
	QList<Expression*> arguments;


	/*methods*/
	static ValueMethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification = NULL );

	void createMethodRef(Method* calledMethod);

};
