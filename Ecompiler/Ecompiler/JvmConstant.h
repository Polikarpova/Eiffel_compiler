#pragma once
#include "enums.h"

struct JvmConstant
{
	enum JvmConstantType type;
	union JvmConstantValue value;
};