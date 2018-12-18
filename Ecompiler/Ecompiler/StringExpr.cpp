#include "StringExpr.h"
#include "JvmConstant.h"
#include "Method.h"
#include "EiffelClass.h"

StringExpr::StringExpr(void)
	: Expression()
{
	this->type = EiffelProgram::currentProgram->findClass("STRING")->getType();
}


StringExpr::~StringExpr(void)
{
}

/*static*/ StringExpr* StringExpr::create(Method* mtd, struct NExpr* expr) {
	
	StringExpr* se = new StringExpr();

	se->currentMethod = mtd;
	se->tree_node = expr;
	se->string = QString(expr->value.String);

	JvmConstant jc = { UTF8_VALUE, 0, false };

	//-----------------String-----------------//
	//имя класса
	jc.type = UTF8_VALUE;
	jc.value.utf8 = &(se->string);
	short int utf8 = se->currentMethod->metaClass->constantTable.put(jc);
		
	// String Constant
	jc.type = STRING_N;
	jc.value.string_const = utf8;
	se->constTableN = se->currentMethod->metaClass->constantTable.put(jc);

	qDebug("created StringExpr (literal): %s. In method: %s", expr->value.String, mtd->tree_node->name);

	return se;
}


ByteCode& StringExpr::toByteCode(ByteCode &bc)
{
	// загрузить строковую константу
	if(constTableN < 256)
		bc.ldc(constTableN);
	else
		bc.ldc_w(constTableN);
	return bc;
}