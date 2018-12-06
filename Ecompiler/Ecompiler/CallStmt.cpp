#include "CallStmt.h"
#include "Method.h"

CallStmt::CallStmt(void)
{
}


CallStmt::~CallStmt(void)
{
}

/*static*/ CallStmt* CallStmt::create(Method* mtd, struct NExpr* expr) {

	//mtd - метод, где всё происходит
	//m - метод, который вызван
	Method* m = 0;

	bool success = false;
	CallStmt* cs = new CallStmt();

	cs->currentMethod = mtd;

	//проверка на ошибулечки
	if ( expr->type != RefnCallE ) {
	
		EiffelProgram::currentProgram->logError(
			QString("semantic"), 
			QString("Invalid procedure call"),
			expr->loc.first_line);
	
		return NULL;

	} else {
	
		QString name = QString( expr->value.id ).toLower();
		m = mtd->metaClass->findMethod(name);
		if ( !m ) {
			
			EiffelProgram::currentProgram->logError(
				QString("semantic"), 
				QString("Call undefined procedure: %1 is not a feature of class %2")
					.arg(name, mtd->metaClass->name()),
				expr->loc.first_line);
	
			return NULL;

		} else {
			
			//если m не экспортируется текущему классу
			if ( false ) {
			
				EiffelProgram::currentProgram->logError(
					QString("semantic"), 
					QString("Cannot use feature %1 of class %2: it is not exported to class %3")
						.arg(m->name, m->metaClass->name(), mtd->metaClass->name()),
					expr->loc.first_line);
	
				return NULL;

			} else {
			
				if ( !m->type->isVoid() ) {
				
					EiffelProgram::currentProgram->logError(
						QString("semantic"), 
						QString("Invalid procedure call: routine %1 is a function, procedure expected")
							.arg(m->name),
						expr->loc.first_line);
	
					return NULL;
				}
			}
		}
	}

	//приписать номер к узлу константы
	cs->createMethodRef(m);

	//проверка соответствия количества и типов выражений
		//аргументы в QList<Expression>
		//в Method функция checkArguments

	success = true;

	return success? cs : 0;
}

void CallStmt::createMethodRef(Method* callMethod) {

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

	//-----------------Class-----------------//
	//имя класса
	jc.type = UTF8_VALUE;
	jc.value.utf8 = new QString(callMethod->metaClass->name());
	short int class_utf8 = currentMethod->metaClass->constantTable.put(jc);
		
	// Class Constant
	jc.type = CLASS_N;
	jc.value.class_const = class_utf8;
	short int class_class = currentMethod->metaClass->constantTable.put(jc);

	//-----------------Name&Type-----------------//
	//имя метода
	jc.type = UTF8_VALUE;
	jc.value.utf8 = new QString(callMethod->name);
	short int method_name_utf8 = currentMethod->metaClass->constantTable.put(jc);
	
	//дескриптор метода
	jc.type = UTF8_VALUE;
	jc.value.utf8 = new QString(callMethod->descriptor);
	short int method_descriptor_utf8 = currentMethod->metaClass->constantTable.put(jc);
	
	//Name&Type Constant
	jc.type = NAME_AND_TYPE;
	jc.value.name_and_type[UTF8_NAME] = method_name_utf8;
	jc.value.name_and_type[UTF8_TYPE] = method_descriptor_utf8;
	short int method_name_and_type = currentMethod->metaClass->constantTable.put(jc);

	//-----------------MethodRef-----------------//
	//MethodRef Constant
	jc.type = METHOD_REF;
	jc.value.method_ref[CONST_CLASS] = class_class;
	jc.value.method_ref[CONST_NAMEnTYPE] = method_name_and_type;
	this->methodref_constN = currentMethod->metaClass->constantTable.put(jc);
}