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
	static MethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );

	void createMethodRef(Method* calledMethod);

	// при генерации учесть, что метод м.б. конструктором: использовать invokespecial вместо invokevirtual
	// noQualify: опустить загрузку ссылки на объект
	ByteCode& toByteCode(ByteCode &, bool noQualify = false);

};
