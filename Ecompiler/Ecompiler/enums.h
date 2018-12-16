#pragma once
#include <qstring.h>


enum JvmConstantType {
	UTF8_VALUE = 1,
	INT4_VALUE = 3,
	FLOAT_VALUE = 4,  //заменено из Real
	CLASS_N = 7,
	STRING_N = 8,
	FIELD_REF = 9,
	METHOD_REF = 10,
	NAME_AND_TYPE = 12,
};


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