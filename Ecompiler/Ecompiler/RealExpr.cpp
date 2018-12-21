#include "RealExpr.h"
#include "JvmConstant.h"
#include "Method.h"
#include "EiffelClass.h"

RealExpr::RealExpr(void)
	: Expression()
{
	this->constTableN = -1;
	this->type = EiffelProgram::currentProgram->findClass("REAL")->getType();
}


RealExpr::~RealExpr(void)
{
}

/*static*/ RealExpr* RealExpr::create(Method* mtd, struct NExpr* expr) {
	
	RealExpr* re = new RealExpr();

	re->currentMethod = mtd;
	re->tree_node = expr;
	re->Real = expr->value.Real;

	JvmConstant jc = { UTF8_VALUE, 0, false };

	//-----------------Real-----------------//
	jc.type = FLOAT_VALUE;
	jc.value.real = re->Real;
	re->constTableN = re->currentMethod->metaClass->constantTable.put(jc);

	qDebug("created RealExpr (literal): %f. In method: %s", re->Real, mtd->tree_node->name);

	return re;
}


ByteCode& RealExpr::toByteCode(ByteCode &bc)
{
	// загрузить число с плавающей запятой
	bc.ldc(this->constTableN);

	return bc;
}