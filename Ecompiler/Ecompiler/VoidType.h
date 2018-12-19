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

	bool canCastTo(const EiffelType* otherType) const {
		return false; // Void нельзя ни к чему приводить
	}

	QString descriptor() {return QString("V");}
	QString toReadableString() const {return "VOID";};

	static VoidType* singleton;
	static VoidType* instance() { if(!singleton){singleton=new VoidType();} return singleton;};
};