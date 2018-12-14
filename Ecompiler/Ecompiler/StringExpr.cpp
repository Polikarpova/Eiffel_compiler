#include "StringExpr.h"
#include "JvmConstant.h"
#include "Method.h"

StringExpr::StringExpr(void)
	: Expression()
{
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
	jc.value.utf8 = new QString(se->string);
	short int utf8 = se->currentMethod->metaClass->constantTable.put(jc);
		
	// String Constant
	jc.type = STRING_N;
	jc.value.string_const = utf8;
	se->constTableN = se->currentMethod->metaClass->constantTable.put(jc);

	return se;
}
