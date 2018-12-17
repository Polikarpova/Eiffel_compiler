#include "MetaClass.h"
#include "EiffelClass.h"
#include "EiffelProgram.h"
#include "Feature.h"
#include "Method.h"
#include "Field.h"

#include "ByteCode.h"

MetaClass::MetaClass(EiffelProgram* program, const QString& name)
{
	this->program = program;
	this->parent = NULL;
	this->isAbstract = false;
	this->_exprType = NULL;

	this->_name = name;

	initConstants();
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

EiffelClass* MetaClass::getType()
{
	if(!_exprType)
		_exprType = new EiffelClass(this);
	return _exprType;
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
					// remember flag: method is creator
					mtd_creator->isCreator = true;
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
				
				continue;
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
		
 
	foreach(Method* mtd, this->methods)
	{
		mtd->createBody();
	}

	return success;
}

bool MetaClass::createInheritance(struct NInheritFromClass* node)
{
	QString name(node->className);
	name = name.toUpper();

	if(name.compare("NONE") == 0) {
		program->logError(
			QString("semantic"), 
			QString("Inheritance form special frozen class `NONE` is not allowed; (inheritance clause in class `%1`)")
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
					QString("Redefine subclause `%1` does not denote redefined feature of class %2; parent %3 does not have such feature")
						.arg(name, this->name(), this->parent->name()),
					i->loc.first_line);
			}

			Feature* this_feature = this->findFeature(name, false);

			if( ! this_feature )
			{
				program->logError(
					QString("semantic"), 
					QString("Redefine subclause lists feature `%1`, but class %2 does not redefined it")
						.arg(name, this->name(), this->parent->name()),
					i->loc.first_line);
			}

			if( parent_feature && this_feature )
			{
				if( parent_feature->isField() && this_feature->isField() )
				{
					program->logError(
						QString("semantic"), 
						QString("Redefine attribute of class %1 with attribute `%2` in class %3 (you may redefine it with function instead)")
							.arg(this->parent->name(), name, this->name()),
						i->loc.first_line);
				}
				else if( ! this_feature->type->canCastTo(parent_feature->type) )
				{
					program->logError(
						QString("semantic"), 
						QString("Redefined feature`s base type is incompatible with the base type of a feature in parent class %1 (feature `%2` in class %3)")
							.arg(this->parent->name(), name, this->name()),
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
	return true;
}


bool MetaClass::generateCode(const QDir& code_dir)
{
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
 //   u2 this_class;
 //   u2 super_class;
 //   u2 interfaces_count;
 //   u2 interfaces[interfaces_count];


 //   u2 fields_count;
 //   field_info fields[fields_count];


 //   u2 methods_count;
 //   method_info methods[methods_count];
	this->methods_to_ByteCode(bc);

 //   u2 attributes_count;
 //   attribute_info attributes[attributes_count];
 // }


	// создать путь до нужной папки
	QDir package_dir(code_dir);
	package_dir.mkpath(this->javaPackage());
	package_dir.cd(this->javaPackage());
	// записываем байт-код в файл
	QString filepath = package_dir.absoluteFilePath( this->name() + ".class");
	bc.toFile(filepath);

	// сохранить также лог 

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
		bc.log(QString("Field N %1   \"%2\":").arg(i++).arg(Field_name));
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
		bc.log(QString("Method N %1   \"%2\":").arg(i++).arg(Method_name));
		Method_1->to_ByteCode(bc);
	}
	return bc;
}


bool MetaClass::isNameConflicting(const QString& upperName) {
	return 
		upperName==("NONE") // нужно ли в конечном итоге?
		|| EiffelProgram::currentProgram -> findClass(upperName) != NULL;
}
