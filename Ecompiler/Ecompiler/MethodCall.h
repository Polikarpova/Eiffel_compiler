#pragma once
#include "Expression.h"
#include "QList"

class Method;

class MethodCall : public Expression
{

public:
	MethodCall(void);
	~MethodCall(void);

	/*fields*/

	short int methodref_constN;

	//* метод, к которому производится доступ
	Method* calledMethod;

	//* список аргументов метода
	QList<Expression*> arguments;


	/*methods*/
	static MethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList, Expression* qualification = NULL );

	void createMethodRef(Method* calledMethod);

};
