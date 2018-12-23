#include "MetaClass.h"
#include "EiffelClass.h"
#include "EiffelProgram.h"
#include "Feature.h"
#include "Method.h"
#include "Field.h"
#include "MethodCall.h"

#include "EiffelArray.h"

#include "RTLMetaClass.h"
#include "ByteCode.h"
#include "SpecialMethod.h"

MetaClass::MetaClass(EiffelProgram* program, const QString& name)
{
	this->program = program;
	this->parent = NULL;
	this->isAbstract = false;
	this->_exprType = NULL;
	this->parentsCreatorRef = NULL;

	this->_name = name;
}

MetaClass::~MetaClass() {
	if(!_exprType)
		delete _exprType;
};

void MetaClass::initConstants()
{
	//short int name_constN, class_constN, super_class_constN;

	JvmConstant jc = { UTF8_VALUE, 0, false };
	QString buffer;

	// имя атрибута Code
	jc.type = UTF8_VALUE;
	buffer = "Code";
	jc.value.utf8 = & buffer;
	this->code_constN = this->constantTable.put(jc);
	
	// имя класса
	jc.type = UTF8_VALUE;
	buffer = this->fullJavaName();
	jc.value.utf8 = & buffer;
	this->name_constN = this->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = this->name_constN;
	this->class_constN = this->constantTable.put(jc);
	

	if(this->parent)
	{
		// имя класса
		jc.type = UTF8_VALUE;
		buffer = this->parent->fullJavaName();
		jc.value.utf8 = & buffer;
		int parent_name_constN = this->constantTable.put(jc);
		
		// Class Constant
		jc.type = CLASS_N;
		jc.value.class_const = parent_name_constN;
		this->super_class_constN = this->constantTable.put(jc);
	}
}

/*static*/ MetaClass* MetaClass::create(struct NClass* class_node)
{
	// check name collisions
	EiffelProgram* program = EiffelProgram::currentProgram;
	QString name(class_node->className);
	name = name.toUpper();

	if(isNameConflicting(name))
	{
		program->logError(
			QString("semantic"), 
			QString("Redifiniton of class %1")
				.arg(name),
			class_node->loc.first_line);
	
		return NULL;
	}
	else
	{
		MetaClass* mc = new MetaClass(program, name);
		mc->tree_node = class_node;
		
		if(mc)
			program->classes[ mc->name() ] = mc;

		// report creation
		qDebug("Created class:\t `%s`", class_node->className);

		return mc;
	}
}

Field* MetaClass::findField(const QString& lowerName, bool lookInParents /*= true*/)
{
	Field* p = fields.value(lowerName, NULL);
	if(!p && lookInParents && this->parent)
	{
		p = this->parent->findField(lowerName, lookInParents);
	}

	return p;
}
Method* MetaClass::findMethod(const QString& lowerName, bool lookInParents /*= true*/)
{
	Method* p = methods.value(lowerName, NULL);
	if(!p && lookInParents && this->parent)
	{
		p = this->parent->findMethod(lowerName, lookInParents);
	}

	return p;
}
Feature* MetaClass::findFeature(const QString& lowerName, bool lookInParents /*= true*/)
{
	Feature* p = findMethod(lowerName, false);
	if(!p)
	{
		p = findField(lowerName, false);
	}
	if(!p && lookInParents && this->parent)
	{
		p = this->parent->findFeature(lowerName, lookInParents);
	}

	return p;
}
Method* MetaClass::findDefaultConstructor()
{
	Method* creator = NULL;
	foreach(Method* mtd, this->methods)
	{
		if(mtd->isCreator && mtd->exactNumberOfArgs() == 0)
		{
			creator = mtd;
			break;
		}
	}

	return creator;
}

EiffelType* MetaClass::getType()
{
	if(!_exprType)
		_exprType = new EiffelClass(this);
	return _exprType;
}
void MetaClass::setType(EiffelType* newType)
{
	//if(this->_exprType)
	//	delete this->_exprType;
	this->_exprType = newType;
	
	//// set this type to all constructors
	//foreach(Method* mtd, this->methods)
	//{
	//	if(mtd->isCreator)
	//	{
	//		mtd->type = this->_exprType;
	//	}
	//}
}


bool MetaClass::createFeatures() {

	bool success = false;

	{
	struct NFeatureList* List = tree_node->featureList;
	// iterate
	if(List) {
		for(struct NFeature* i = List->first ;  ; i = i->next )
		{
			success = Feature::create(this, i);

			if(i == List->last) break;
		}
	}
	}
	
	// Iterate creators list
	{
	// struct NIdList* creationList; // NULL если отсутствует
	struct NIdList* List = tree_node->creationList;
	// iterate
	if(List) {
		for(struct NId* i = List->first ;  ; i = i->next )
		{
			QString name(i->id);
			name = name.toLower();
			
			if( findField(name, false) != NULL )
			{
				program->logError(
					QString("semantic"), 
					QString("Cannot use attribute %1 as a constructor procedure of class %2")
						.arg(name, this->name()),
					i->loc.first_line);

				break;
			}
			else
			{
				Method* mtd_creator = findMethod(name, false);
				if( ! mtd_creator )
				{
					program->logError(
						QString("semantic"), 
						QString("Undefined identifier %1 used as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
						i->loc.first_line);
				}
				else if( ! mtd_creator->isVoid() )
				{
					program->logError(
						QString("semantic"), 
						QString("Cannot use function %1 as a constructor of class %2. Procedure name expected")
						.arg(name, this->name()),
						i->loc.first_line);
				} 
				else
				{
					// !!! Проверить, что нет других конструкторов с такой же сигнатурой !
					// ...

					// remember flag: method is creator
					mtd_creator->isCreator = true;
					
					// threat this method as constructor
					QString newJavaName = "<init>";

					// change class constant (грубая замена)
					int n = this->constantTable.searchUtf8(mtd_creator->javaName);
					if(n == -1)
						throw "utf8 not found. [in MetaClass.createFeatures()]";
					*(constantTable.get(n).value.utf8) = newJavaName;

					mtd_creator->javaName = newJavaName;

					success = true;
				}
			}
			if(i == List->last) break;
		}
	}
	}

	return success;
}
bool MetaClass::round3()
{
	bool success = false;

	/* ПРОВЕРИТЬ число родителей и запомнить родителя (ANY по умолчанию),
	   а также проверить переопределения */
	this->parent = NULL;

	struct NInheritFromClassList* List =  tree_node->inheritance;
	// iterate
	if(List) {
		for(struct NInheritFromClass* i = List->first ;  ; i = i->next )
		{
			if(this->parent != NULL) {
				program->logError(
					QString("semantic"), 
					QString("Declaring multiple parents for class `%1`; this feature of Eiffel language is not supported")
						.arg(this->name()),
					i->loc.first_line);
				
				break;
			}

			if( !createInheritance(i) )
			{
				continue;
			}

			if(i == List->last) break;
		}
	}
	
	if(this->parent == NULL) {
		// set ANY as parent
		MetaClass* ancestor = program->findClass("ANY");
		if(ancestor)
		{
			this->parent = ancestor;
			success = true;
		}
		else
		{
			program->logError(
				QString("internal"), 
				QString("/!\\ Class `ANY` is not known /!\\"),
				this->tree_node->loc.first_line);
			success = false;
		}
	}
	// ... */
	
	qDebug("class `%s` inherit from class `%s`", this->name().toLocal8Bit().data(), this->parent->name().toLocal8Bit().data());
		

	// после заполнения предка
	this->initConstants();
 
	return success;
}
bool MetaClass::round4()
{
	bool success = false;

	foreach(Method* mtd, this->methods)
	{
		bool b = mtd->createBody();
		success = success && b;
	}

	// подготовить специальные методы (конструкторы и геттеры)
	makeSpecialMethods();

	return success;
}

bool MetaClass::createInheritance(struct NInheritFromClass* node)
{
	QString name(node->className);
	name = name.toUpper();

	if(name.compare("NONE") == 0) {
		program->logError(
			QString("semantic"), 
			QString("Inheritance form special frozen class `NONE` is not allowed (inheritance clause in class `%1`)")
				.arg(this->name()),
			node->loc.first_line);
				
		return false;
	}

	// предок
	MetaClass* ancestor = program->findClass(name);

	if(ancestor == NULL) {
		program->logError(
			QString("semantic"), 
			QString("Undefined class `%1` is used as parent of class %2")
				.arg(node->className, this->name()),
			node->loc.first_line);
				
		return false;
	}
	
	this->parent = ancestor;
	// ^ set parent successfully !
	
	struct NIdList* List =  node->redefineList;
	// iterate
	if(List) {
		for(struct NId* i = List->first ;  ; i = i->next )
		{
			QString name(i->id);
			name = name.toLower();

			Feature* parent_feature = this->parent->findFeature(name, true);

			if( ! parent_feature )
			{
				program->logError(
					QString("semantic"), 
					QString("Redefine subclause `%1` does not denote redefined feature of class `%2`; parent `%3` does not have such feature.")
						.arg(name, this->name(), this->parent->name()),
					i->loc.first_line);
			}

			Feature* this_feature = this->findFeature(name, false);

			if( ! this_feature )
			{
				program->logError(
					QString("semantic"), 
					QString("Redefine subclause lists feature `%1` of class `%3`, but class `%2` does not redefine it.")
						.arg(name, this->name(), parent_feature->metaClass->name()),
					i->loc.first_line);
			}

			if( parent_feature && this_feature )
			{
				/*if( parent_feature->isField() && this_feature->isField() )
				{
					program->logError(
						QString("semantic"), 
						QString("Redefining attribute `%2` of class `%1` again with attribute in class `%3` (you may redefine it with function instead).")
							.arg(parent_feature->metaClass->name(), name, this->name()),
						i->loc.first_line);
				}
				else*/ if( ! this_feature->type->canCastTo(parent_feature->type) )
				{
					program->logError(
						QString("semantic"), 
						QString("Redefined feature `%3.%2` has base type is incompatible with the base type of inherited feature `%1.%2`.\nType of current feature: \t%4\nType of parent`s feature:\t%5")
							.arg(parent_feature->metaClass->name(), name, this->name(),
							this_feature->type->toReadableString(), parent_feature->type->toReadableString()),
						i->loc.first_line);
				}
				else if( parent_feature->isField() == this_feature->isMethod() ) // one is field, another is method
				{
					/********* /!\ ********** /
					Мы допускаем, вопреки результатам экспериментов с Eiffel,
					возможность переопределять поля методами без аргументов и наоборот.
					/********* /!\ ***********/

					//Field*  field_fe  = (Field*)  ( parent_feature->isField() ? parent_feature : this_feature );
					Method* method_fe = (Method*) ( parent_feature->isMethod()? parent_feature : this_feature );

					if(method_fe->paramCount != 0) {
						program->logError(
							QString("semantic"), 
							  (method_fe == this_feature
							   ?
							   QString("Redefining an attribute `%2` of class %1 with a function with parameters in class %3 (no arguments are required in order to provide the same usage of a feature)")
							   :
							  QString("Redefining a function with parameters of class %1 with an attribute `%2` in class %3 (you can redefine it with a routine only)")
							  ).arg(this->parent->name(), name, this->name()),
							i->loc.first_line);
					}

					// ... проверки не дописаны
				}
			}


			if(i == List->last) break;
		}
	}

	// ... проверить конфликты имён с наследуемыми членами

	return true;
}

bool MetaClass::makeSpecialMethods()
{
	//Method* mtd;
	SpecialMethod* static_void_main;
	EiffelType *void_type = VoidType::instance();

	//// конструктор <init> ...

	// найти конструктор по умолчанию: который первый без параметров
	Method* default_eiffel_creator = this->findDefaultConstructor();

	if(default_eiffel_creator)
	{
		// создать метод `public static void main(java.lang.String args[])`
		EiffelSTRING str_type = EiffelSTRING();
		EiffelArray arg_type = EiffelArray(&str_type);

		static_void_main = new SpecialMethod(this, void_type, "main" ,  QList<LocalVariable>() << LocalVariable(&arg_type,"args") );
		static_void_main->javaName = "main"; // after auto-decorating of special names
		static_void_main->addFlags = ACC_STATIC;
		
		static_void_main->initConstants();

		// (Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );
		MethodCall* specialcall = MethodCall::create(static_void_main, default_eiffel_creator);
	
		ByteCode &bc = static_void_main->bytecode;
		//bc.new_( this->class_constN );
		specialcall->toByteCode(bc, true);
		bc.return_();

		this->methods[ static_void_main->name ] = static_void_main;

		delete specialcall;


		// create MethodRef to parent`s constructor ...
		// to use in constructors of this class
		//// create(Method* context_mtd, Method* calledMethod, struct NExprList* argList = NULL, Expression* qualification = NULL );
		this->parentsCreatorRef = MethodCall::create(default_eiffel_creator, this->parent->findDefaultConstructor());
		this->parentsCreatorRef->noCreate = true;
	}

	return true;
}

bool MetaClass::generateCode(const QDir& code_dir)
{
	// сгенерировать методы заранее
	ByteCode bc_methods_pool;
	this->methods_to_ByteCode(bc_methods_pool);


	// составляем байт-код и записываем в файл ...

	ByteCode bc;

 // ClassFile {
 //	  u4 magic;
 //   u2 minor_version;
 //   u2 major_version;
 //   u2 constant_pool_count;
 //   cp_info constant_pool[constant_pool_count-1];
	this->constantTable.to_ByteCode(bc);

 //   u2 access_flags;
	bc.u2(0x0001); //флаги
 //   u2 this_class;
	bc.u2(class_constN);
	bc.log(QString("Current class,  num CONSTANT_Class =")+bc.CombinedPrint(class_constN, 2));
 //   u2 super_class;
	bc.u2(super_class_constN);
	bc.log(QString("Super class,  num CONSTANT_Class =")+bc.CombinedPrint(super_class_constN, 2));
 //   u2 interfaces_count;
	bc.u2(0x0000); //количество интерфейсов
 //   u2 interfaces[interfaces_count];


 //   u2 fields_count;
 //   field_info fields[fields_count];
	this->fields_to_ByteCode(bc);

 //   u2 methods_count;
 //   method_info methods[methods_count];
	bc.append(bc_methods_pool);

 //   u2 attributes_count;
	bc.u2(0x0000);
 //   attribute_info attributes[attributes_count];
 // }


	// создать путь до нужной папки
	QDir package_dir(code_dir);
	package_dir.mkpath(this->javaPackage());
	package_dir.cd(this->javaPackage());
	// записываем байт-код в файл
	QString filepath = package_dir.absoluteFilePath( this->name() + ".class");
	bc.toFile(filepath);


	// сохраняем Лог в текстовый файл с именем <Имя_Класса>.log
	bc.LogToFile((QString)package_dir.absoluteFilePath( this->name() + ".log"));

	return true;
}


ByteCode& MetaClass::fields_to_ByteCode(ByteCode &bc) {
//пишем в ByteCode данные обо всех полях

	short int Fields_pool_count, i=0;
	QList<Field*> fieldsVals;
	Field* Field_1;

	bc.log("").log(QString("Writing Fields_pool ..."));

	Fields_pool_count = fields.size();
 	bc.u2(Fields_pool_count); //длина Таблицы полей
	bc.log(QString("Fields_pool_count")+bc.CombinedPrint(Fields_pool_count, 2));

	//вариант без указания Имени_поля (только Номер_поля)
/*	fieldsVals = fields.values();
	foreach(Field_1, fieldsVals)
	{
		bc.log(QString("Field N %1:").arg(i++));
		Field_1->to_ByteCode(bc);
	} */

	//вариант с указанием Имени_поля
	foreach(QString Field_name, fields.keys()) //итерация по ключам
	{
		Field_1 = fields[Field_name];
		bc.log(QString("Field N %1   \"%2\" (`%3`):").arg(i++).arg(Field_name, Field_1->javaName));
		Field_1->to_ByteCode(bc);
	}
	return bc;
}

ByteCode& MetaClass::methods_to_ByteCode(ByteCode &bc) {
//пишем в ByteCode данные обо всех методах

	short int Methods_pool_count, i=0;
	Method* Method_1;

	bc.log("").log(QString("Writing Methods_pool ..."));

	Methods_pool_count = methods.size();
 	bc.u2(Methods_pool_count); //длина Таблицы методов
	bc.log(QString("Methods_pool_count")+bc.CombinedPrint(Methods_pool_count, 2));

	//с указанием Имени_метода
	foreach(QString Method_name, methods.keys())
	{
		Method_1 = methods[Method_name];
		bc.log(QString("Method N %1   \"%2\" (`%3`):").arg(i++).arg(Method_name, Method_1->javaName));
		Method_1->to_ByteCode(bc);
	}
	return bc;
}


bool MetaClass::isNameConflicting(const QString& upperName) {
	return 
		upperName==("NONE") // нужно ли в конечном итоге?
		|| EiffelProgram::currentProgram -> findClass(upperName) != NULL;
}
