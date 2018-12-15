#include "VoidType.h"


VoidType::VoidType(void)
{
}

VoidType::VoidType(struct NType* type)
{
	this->tree_node = type;
}

VoidType::~VoidType(void)
{
}

bool VoidType::isVoid() const {

	return true;
}