#include "MethodCall.h"

#include "Method.h"
#include "EiffelClass.h"
#include "EiffelArray.h"

MethodCall::MethodCall(void)
	: Expression()
{
	noCreate = false;
	noQualify = false;
	keepNewReferenceOnStack = true;
	specialCall = false;
	class_of_arr_elem_constN = -1;
	arrayElemType = NULL;
}


MethodCall::~MethodCall(void)
{
	qDeleteAll(arguments);
	arguments.clear();
}

/*static*/ MethodCall* MethodCall::create(Method* context_mtd, Method* calledMethod, struct NExprList* argList /*= NULL*/, Expression* qualification /*= NULL*/ )
{
	int source_line = -1;

	QList<Expression*> arguments;

	//«аполнить массив аргументов выражени€ми
	//arguments << <Expr>*
	struct NExprList* List = argList;
	if(List) {
		for(struct NExpr* i = List->first; i != NULL ; i = i->next) {
			source_line = i->loc.first_line;
			// add expr
			Expression* arg_expr = Expression::create(context_mtd, i);
			if(arg_expr)
				arguments << arg_expr;

			if(i == List->last) break;
		}
	}

	return MethodCall::create(context_mtd, calledMethod, arguments, qualification, source_line);
}

/*static*/ MethodCall* MethodCall::create(Method* context_mtd, Method* calledMethod, QList<Expression*> arguments /*= QList<Expression*>()*/, Expression* qualification /*= NULL*/, int source_line )
{
	////int source_line = -1;

	MethodCall* vmc = new MethodCall();

	////«аполнить массив аргументов выражени€ми
	////arguments << <Expr>*
	//struct NExprList* List = argList;
	//if(List) {
	//	for(struct NExpr* i = List->first; i != NULL ; i = i->next) {
	//		source_line = i->loc.first_line;
	//		// add expr
	//		Expression* arg_expr = Expression::create(context_mtd, i);
	//		if(arg_expr)
	//			vmc->arguments << arg_expr;

	//		if(i == List->last) break;
	//	}
	//}

	vmc->arguments = arguments;

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
					.arg(context_mtd->metaClass->name(), context_mtd->name),
				source_line);
			delete vmc;
			return NULL;
		}

		EiffelType* convertType = 0;

		bool types_ok = vmc->arguments[i]->expressionType()->canCastTo( formal_arg->type, &convertType );

		if(!types_ok)
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Signatures differ in call to routine `%4`.`%1`: cannot convert argument %5 from type `%6` to type `%7`. (In routine: %2.%3)")
					.arg(calledMethod->name, context_mtd->metaClass->name(), context_mtd->name, calledMethod->metaClass->name())
					.arg(i+1)
					.arg(vmc->arguments[i]->expressionType()->toReadableString(),formal_arg->type->toReadableString()),
				source_line);
			delete vmc;
			return NULL;
		}

		// установить узлу преобразование
		if(convertType != 0)
		{
			vmc->arguments[i]->setConversionTo(convertType);
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

void MethodCall::createArrayElemConstants(EiffelType* elemType) {
	
	this->arrayElemType = elemType;

	// Make a constant for Element
	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	if(elemType->isArray()) // многомерный массив
	{
		EiffelProgram::currentProgram->logError(
			QString("internal"), 
			QString("Multidimentional arrays are not supported. Attempt init element of array of type: %1. In MethodCall::createArrayElemConstants()")
				.arg(elemType->toReadableString()),
			this->tree_node->loc.first_line);
		return;
	}
	else if(elemType->isReference()) // массив объектов (в т.ч. строк)
	{
		//-----------------Class-----------------//
		//им€ класса
		jc.type = UTF8_VALUE;
		buffer = ((EiffelClass*)elemType)->metaClass->fullJavaName(); // ->descriptor(); // 
		jc.value.utf8 = & buffer;
		short int class_utf8 = currentMethod->metaClass->constantTable.put(jc);
		// Class Constant
		jc.type = CLASS_N;
		jc.value.class_const = class_utf8;
		this->class_of_arr_elem_constN = currentMethod->metaClass->constantTable.put(jc);
	}
}

ByteCode& MethodCall::toByteCode(ByteCode &bc, bool noQualify)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();
	bool isArray = base_type->isArray(); // массив

	if(base_type->isArray()) // массив
	{
		return arrayCreation(bc);
		// exit
	}

	//noQualify = noQualify && ! this->noCreate;

	//bc.log("MethodCall : object ...");

	bool omitQualification = 
		//this->calledMethod->isCreator ||
		isArray ||
		noQualify ||
		this->noQualify ||
		(this->calledMethod->addFlags & ACC_STATIC)
		;


	if( !omitQualification )
	{
		bc.log(QString("load qualification for method %1 ...")
			.arg(this->calledMethod->name));

		// дл€ динамического метода с this
		// load a reference to an object ...
		// call qualification as this->left
		if(this->left)
			this->left->toByteCode(bc); // load qualification
		else
			bc.aload_0(); // load Current
	}

	if( !this->noCreate && this->calledMethod->isCreator )
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

	if(this->calledMethod->isCreator || this->specialCall)
	{
		bool is_void = ! 
				( // возвращает значение, если:
				this->calledMethod->isCreator && // конструктор
				this->keepNewReferenceOnStack &&
				!this->noCreate )
			||
			this->calledMethod->isVoid()
			;

		bc.invokespecial(methodref_constN,
			this->calledMethod->exactNumberOfArgs(),
			is_void);
	}
	else
	{
		bc.invokevirtual(methodref_constN,
			this->calledMethod->exactNumberOfArgs(),
			this->calledMethod->isVoid());
	}

	if ( !this->calledMethod->isVoid() )
		applyI2F(bc);
	
	return bc;
}

ByteCode& MethodCall::generateCreation(ByteCode &bc)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();

	if(base_type->isReference()) // объект
	{
		bc.log(QString("generate code for Creation (new*) of %1 ...")
			.arg(base_type->toReadableString()));

		bc.new_( this->class_of_called_mtd_constN );
		
		if(this->keepNewReferenceOnStack)
		{
			bc.dup();
		}
	}


	return bc;
}

ByteCode& MethodCall::arrayCreation(ByteCode &bc)
{
	EiffelType* base_type = this->calledMethod->metaClass->getType();

	if(base_type->isArray()) // массив
	{
		bc.log(QString("generating code for Array Creation (new*) of [%1] ...")
			.arg(this->arrayElemType->toReadableString()));

		int var_lower_i , var_upper_i;
		LocalVariable *par_lower , *par_upper;
		Expression *arg_lower , *arg_upper;
			
		par_lower = this->calledMethod->findLocalVar("lower");
		par_upper = this->calledMethod->findLocalVar("upper");

		bool ok = 
			par_lower && par_upper
			&& this->calledMethod->exactNumberOfArgs() == 2
			&& this->calledMethod->name == "make";

		if( !par_lower || !par_upper ) {
			
			bc.log("/!\\ Array will not be created.");

			EiffelProgram::currentProgram->logError(
				QString("internal"), 
				QString("Cannot find method `make(lower [= 0], upper [= n])` in routine: %1.%2")
					.arg(currentMethod->metaClass->name(), currentMethod->name),
				this->tree_node->loc.first_line);
			return bc;
			////bc.pop();
		}

		var_lower_i = par_lower->n - 1;
		var_upper_i = par_upper->n - 1;

		arg_lower = this->arguments[ var_lower_i ];
		arg_upper = this->arguments[ var_upper_i ];

		// ignore 1st argument: default is 0

		//// array size  =  n + 1
		//// expr for n
		//arg_upper->toByteCode(bc);
		//bc.iconst_(1);
		//bc.iadd();

		// : verify indices, add 1 to arg_upper and put it onto stack
		MethodCall* call_helper = EiffelProgram::currentProgram->callHelper(currentMethod, 
			"verifyArrayMake", 
			QList<Expression*>()
			<< arg_lower
			<< arg_upper
		);
		call_helper->toByteCode(bc);

		// array size is loaded onto stack

		EiffelType* elem_type = this->arrayElemType;
		
		if(elem_type->isArray()) // многомерный массив
		{
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Multidimentional arrays not supported. Attempt to create an array of type: %1. In routine: %2.%3")
					.arg(base_type->toReadableString())
					.arg(currentMethod->metaClass->name(), currentMethod->name),
				this->tree_node->loc.first_line);
		}
		else if(elem_type->isInteger()) // массив целых чисел
		{
			bc.newarray( 10 ); // INT constant
		}
		else if(elem_type->isReference()) // массив объектов (в т.ч. строк)
		{
			// Check a constant for Element
			if(class_of_arr_elem_constN < 1)
			{
				EiffelProgram::currentProgram->logError(
					QString("internal"), 
					QString("class_of_arr_elem_constN variable is not set. In MethodCall::arrayCreation()"),
					this->tree_node->loc.first_line);
			}

			bc.anewarray( class_of_arr_elem_constN ); // Element CLASS constant_N
		}
	}


	return bc;
}
