#pragma once
#include <qstring.h>

#define UTF8_NAME 0
#define UTF8_TYPE 1

#define CONST_CLASS 0
#define CONST_NAMEnTYPE 1

union JvmConstantValue {

	long int int4;
	float real;
	QString* utf8;
	short int	string_const, 
				class_const,
				name_and_type[2],
				method_ref[2],
				field_ref[2];
};

enum JvmConstantType {
	INT4_VALUE,
	FLOAT_VALUE = 4, // renamed:  real -> float
	UTF8_VALUE,
	STRING_N,
	CLASS_N,
	NAME_AND_TYPE,
	METHOD_REF,
	FIELD_REF
};