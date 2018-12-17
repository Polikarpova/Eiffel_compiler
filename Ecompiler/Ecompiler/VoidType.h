#pragma once
#include "EiffelType.h"

class VoidType : public EiffelType
{

public:
	
	VoidType(void);
	VoidType(struct NType* type);
	~VoidType(void);

	/*methods*/

	bool isVoid() const; // { return true; } -- see .cpp
	QString descriptor() {return QString("V");}


	static VoidType* singleton;
	static VoidType* instance() { if(!singleton){singleton=new VoidType();} return singleton;};
};