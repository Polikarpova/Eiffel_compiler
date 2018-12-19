#pragma once
#include "Statement.h"
#include "ThenPart.h"

class ThenList : public Statement
{

public:

	ThenList(void) {this->currentMethod = 0;}
	//ThenList(Method* mtd) {
	//	this->currentMethod = mtd;
	//}
	~ThenList(void) {
		//this->body.clear();
	}

	QList<ThenPart*> list;

	bool create(Method* mtd, struct NThenPartList* List);

	virtual ByteCode& toByteCode(ByteCode &bc);
};
