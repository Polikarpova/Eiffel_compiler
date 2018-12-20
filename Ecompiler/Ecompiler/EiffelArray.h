#pragma once
#include "EiffelClass.h"


/** Массив с произвольным типом элемента.
	Доступные операции:
	arr[i]
	arr[i] := val
	arr.
*/
class EiffelArray : public EiffelClass
{

public:
	
	EiffelArray(void)
		: EiffelClass(EiffelProgram::currentProgram->findClass("ARRAY"))
	{
		this->elementType = NULL;
	};

	EiffelArray(EiffelType * elementType)
		: EiffelClass(EiffelProgram::currentProgram->findClass("ARRAY"))
	{
		this->elementType = elementType;
	};
	~EiffelArray(void) {};

	/*fields*/
	EiffelType * elementType;


	virtual bool isReference() const { return true; }
	virtual bool isArray() const { return true; }

	virtual bool canCastTo(const EiffelType* otherType) const;
	QString descriptor() { return QString("[%1").arg(elementType->descriptor()); }
	QString toReadableString() const {return QString("ARRAY[%1]").arg(elementType->toReadableString());};

	/*methods*/
	static EiffelArray* create(struct NType* type);

};