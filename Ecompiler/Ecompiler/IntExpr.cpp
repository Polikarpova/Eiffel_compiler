#include "IntExpr.h"
#include "JvmConstant.h"
#include "Method.h"
#include "EiffelClass.h"

IntExpr::IntExpr(void)
	: Expression()
{
	this->constTableN = -1;
	this->type = EiffelProgram::currentProgram->findClass("INTEGER")->getType();
}


IntExpr::~IntExpr(void)
{
}

/*static*/ IntExpr* IntExpr::create(Method* mtd, struct NExpr* expr) {
	
	IntExpr* ie = new IntExpr();

	ie->currentMethod = mtd;
	ie->tree_node = expr;
	ie->Int = expr->value.Int;

	if ( ie->Int >= 0x8000-1 || ie->Int <= -0x8000 ) {
		
		JvmConstant jc = { UTF8_VALUE, 0, false };

		//-----------------Int-----------------//
		jc.type = INT4_VALUE;
		jc.value.int4 = ie->Int;
		ie->constTableN = ie->currentMethod->metaClass->constantTable.put(jc);
	}

	qDebug("created IntExpr (literal): %d. In method: %s", expr->value.Int, mtd->tree_node->name);

	return ie;
}


ByteCode& IntExpr::toByteCode(ByteCode &bc)
{
	// загрузить целочисленную константу
	if (constTableN != -1) {
	
		if(constTableN < 256)
			bc.ldc(constTableN);
		else
			bc.ldc_w(constTableN);
	} else if ( this->Int >= -1 && this->Int <= 5) {
	
		bc.iconst_(this->Int);
	} else if ( this->Int >= 0x80-1 || this->Int <= -0x80 ) {
			
		bc.bipush(this->Int);
	} else {
		
		bc.sipush(this->Int);
	}

	return bc;
}