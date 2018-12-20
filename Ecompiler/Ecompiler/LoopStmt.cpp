#include "LoopStmt.h"

LoopStmt::LoopStmt(void)
{
	this->currentMethod = 0;
}

LoopStmt::~LoopStmt(void)
{
}

/*static*/ LoopStmt* LoopStmt::create(Method* mtd, struct NLoopStmt* stmt) {

	bool success = true;
	LoopStmt* ls = new LoopStmt();
	ls->currentMethod = mtd;

	

	return success ? ls : 0;
}

/*virtual*/ ByteCode& LoopStmt::toByteCode(ByteCode &bc) {

	return bc.log("/!\\ loopStmt not implemented yet");
}