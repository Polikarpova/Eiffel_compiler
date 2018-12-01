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
	short int	string, 
				class_const,
				name_and_type[2],
				method_ref[2],
				field_ref[2];
};

enum JvmConstantType {
	INT4,
	REAL,
	UTF8,
	STRING,
	CLASS,
	NAME_AND_TYPE,
	METHOD_REF,
	FIELD_REF
};