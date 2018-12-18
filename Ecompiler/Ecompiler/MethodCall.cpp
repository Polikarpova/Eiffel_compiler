#include "MethodCall.h"

#include "Method.h"

MethodCall::MethodCall(void)
	: Expression()
{
}


MethodCall::~MethodCall(void)
{
	qDeleteAll(arguments);
	arguments.clear();
}

/*static*/ MethodCall* MethodCall::create(Method* context_mtd, Method* calledMethod, struct NExprList* argList /*= NULL*/, Expression* qualification /*= NULL*/ )
{
	int source_line = -1;

	MethodCall* vmc = new MethodCall();

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
			QString("Call: wrong number of arguments. Routine `%1` declares %4 formal parameters, but %5 actual arguments were provided. (In routine: %2.%3)")
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

	// set up class constants
	//приписать номер к узлу константы
	vmc->createMethodRef(calledMethod);

	// report creation
	qDebug("created MethodCall: %s(%d params)", calledMethod->name.toLocal8Bit().data(), n_formal_args);

	return vmc;
}


void MethodCall::createMethodRef(Method* calledMethod) {

	/*
		Methodref
			|_______Class
			|			|_______utf8 - имя
			|
			|_______Name&Type
						|_______utf8 - имя
						|
						|_______utf8 - дескриптор метода
	*/

	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	//-----------------Class-----------------//
	//имя класса
	jc.type = UTF8_VALUE;
	buffer = calledMethod->metaClass->name();
	jc.value.utf8 = & buffer;
	short int class_utf8 = currentMethod->metaClass->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = class_utf8;
	short int class_class = currentMethod->metaClass->constantTable.put(jc);

	//-----------------Name&Type-----------------//
	//имя метода
	jc.type = UTF8_VALUE;
	buffer = calledMethod->javaName;
	jc.value.utf8 = & buffer;
	short int method_name_utf8 = currentMethod->metaClass->constantTable.put(jc);
	
	//дескриптор метода
	jc.type = UTF8_VALUE;
	buffer = calledMethod->getDescriptor();
	jc.value.utf8 = & buffer;
	short int method_descriptor_utf8 = currentMethod->metaClass->constantTable.put(jc);
	
	//Name&Type Constant
	jc.type = NAME_AND_TYPE;
	jc.value.name_and_type[UTF8_NAME] = method_name_utf8;
	jc.value.name_and_type[UTF8_DESCR] = method_descriptor_utf8;
	short int method_name_and_type = currentMethod->metaClass->constantTable.put(jc);

	//-----------------MethodRef-----------------//
	//MethodRef Constant
	jc.type = METHOD_REF;
	jc.value.method_ref[CONST_CLASS] = class_class;
	jc.value.method_ref[CONST_NAMEnTYPE] = method_name_and_type;
	this->methodref_constN = currentMethod->metaClass->constantTable.put(jc);
}

ByteCode& MethodCall::toByteCode(ByteCode &bc)
{
	if(this->calledMethod->isCreator)
	{
		bc.invokespecial(methodref_constN,
			this->calledMethod->exactNumberOfArgs(),
			this->calledMethod->isVoid());
	}
	else
	{
		bc.invokevirtual(methodref_constN,
			this->calledMethod->exactNumberOfArgs(),
			this->calledMethod->isVoid());
	}
	return bc;
}
