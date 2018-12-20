#include "MethodCall.h"

#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

MethodCall::MethodCall(void)
	: Expression()
{
	noCreate = false;
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

	//«аполнить массив аргументов выражени€ми
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

	// проверка соответстви€ количества аргументов

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

	// проверка соответстви€ типов аргументов
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
	qDebug("created MethodCall: %s( args: %d )", calledMethod->name.toLocal8Bit().data(), n_formal_args);

	return vmc;
}


void MethodCall::createMethodRef(Method* calledMethod) {

	/*
		Methodref
			|_______Class
			|			|_______utf8 - им€
			|
			|_______Name&Type
						|_______utf8 - им€
						|
						|_______utf8 - дескриптор метода
	*/

	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	//-----------------Class-----------------//
	//им€ класса
	jc.type = UTF8_VALUE;
	buffer = calledMethod->metaClass->fullJavaName();
	jc.value.utf8 = & buffer;
	short int class_utf8 = currentMethod->metaClass->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = class_utf8;
	class_of_called_mtd_constN = currentMethod->metaClass->constantTable.put(jc);

	//-----------------Name&Type-----------------//
	//им€ метода
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
	jc.value.method_ref[CONST_CLASS] = class_of_called_mtd_constN;
	jc.value.method_ref[CONST_NAMEnTYPE] = method_name_and_type;
	this->methodref_constN = currentMethod->metaClass->constantTable.put(jc);
}

ByteCode& MethodCall::toByteCode(ByteCode &bc, bool noQualify)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();
	bool isArray = base_type->isArray(); // массив

	if(base_type->isArray()) // массив
	{
		return arrayCreation(bc);
	}

	//noQualify = noQualify && ! this->noCreate;

	//bc.log("MethodCall : object ...");

	if( !noQualify && ! (this->calledMethod->addFlags & ACC_STATIC) && ! isArray )
	{
		// дл€ динамического метода с this
		// load a reference to an object ...
		// call qualification as this->left
		if(this->left)
			this->left->toByteCode(bc); // load qualification
		else
			bc.aload_0(); // load Current
	}

	if( !noCreate && this->calledMethod->isCreator )
	{
		// создать объект
		this->generateCreation(bc);
	}

	//bc.log("MethodCall : arguments ...");

	// load arguments
	foreach(Expression* arg, this->arguments)
	{
		arg->toByteCode(bc); // load argument
	}

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

ByteCode& MethodCall::generateCreation(ByteCode &bc)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();

	bc.log(QString("generate code for Creation (new*) of %1 ...")
		.arg(base_type->toReadableString()));

	if(base_type->isReference()) // объект
	{
		bc.new_( this->class_of_called_mtd_constN );
		//bc.dup();
	}


	return bc;
}

ByteCode& MethodCall::arrayCreation(ByteCode &bc)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();

	bc.log(QString("generate code for Array Creation (new*) of %1 ...")
		.arg(base_type->toReadableString()));

	if(base_type->isArray()) // массив
	{
		if(this->calledMethod->exactNumberOfArgs() == 2) // make(0,n)
		{
			bc.iconst_(0);
			// expr
			// ...
			bc.iadd();
		}

		EiffelType* elem_type = ((EiffelArray*)base_type)->elementType;
		
		if(elem_type->isInteger()) // массив целых чисел
		{
			bc.newarray( 10 ); // INT constant
		}
		{
			bc.anewarray( class_of_called_mtd_constN ); // CLASS constant_NB
		}
	}


	return bc;
}
