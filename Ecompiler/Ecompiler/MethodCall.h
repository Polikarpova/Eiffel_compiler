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

	short int methodref_constN, class_of_called_mtd_constN, class_of_arr_elem_constN;
	bool noCreate; // пропускать создание (например, объекта с помощью `new`)
	bool noQualify; // пропускать загрузку квалификации
	bool keepNewReferenceOnStack; // нужно ли делать `dup` после `new`
	bool specialCall; // использовать `invokespecial` вместо `invokevirtual`

	//* метод, к которому производится доступ
	Method* calledMethod;

	//* список аргументов метода
	QList<Expression*> arguments;
	
	//* тип элемента массива
	EiffelType* arrayElemType;


	/*methods*/
	static MethodCall* create(Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );

	static MethodCall* create(Method* context_mtd, Method* calledMethod, QList<Expression*> arguments/* = QList<Expression*>() */, Expression* qualification = NULL, int source_line = -1 );

	void createMethodRef(Method* calledMethod);
	void createArrayElemConstants(EiffelType* elemType);

	// при генерации учесть, что метод м.б. конструктором: использовать invokespecial вместо invokevirtual
	// noQualify: опустить загрузку ссылки на объект
	ByteCode& toByteCode(ByteCode &, bool noQualify);
	ByteCode& toByteCode(ByteCode &bc) {return toByteCode(bc, false); };


	ByteCode& generateCreation(ByteCode &);
	ByteCode& arrayCreation(ByteCode &);

};
