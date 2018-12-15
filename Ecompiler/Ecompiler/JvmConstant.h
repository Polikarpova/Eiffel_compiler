#pragma once
#include "enums.h"
#include <qlist.h>

struct JvmConstant
{
	enum JvmConstantType type;		// see "enums.h"
	union JvmConstantValue value;	// see "enums.h"
	
	bool isInvalid;
};

class ConstantTable {

public:

	ConstantTable() {};
	~ConstantTable() {};

	/*fields*/
	QList<JvmConstant> constants; // номер константы = индекс + 1

	/** 
	* ¬озврашает константу по номеру n: [1...N] - номер по таблице констант
	* ј если такого номера нет, то isInvalid = true
	*/
	JvmConstant get(int n)
	{
		if(n >= 1 && n <= constants.size())
			return constants[n-1];

		JvmConstant jc/* = constants[0]*/;
		jc.isInvalid = true;
		return jc;
	}; 
	
	/**
	* ƒобавл€ет константу если еЄ нет
	* ј если така€ уже есть, то только возвращает еЄ номер
	* @return номер константы в таблице : [1...N]
	*/
	int put(JvmConstant cnst)
	{
		int n = searchConstant(cnst);
		if(n >= 1)
			return n;
		
		if(cnst.type == UTF8_VALUE)
		{
			// выделить автономную пам€ть под QString (указатель)
			cnst.value.utf8 = new QString( *cnst.value.utf8 );
		}		
		cnst.isInvalid = false;
		constants.push_back(cnst);
		return constants.size();
	}

	/**
	* »щет константу - копию
	* @return номер константы [1...N]  или -1, если не найдено
	*/
	int searchConstant(const JvmConstant cnst)
	{
		int i = 0;
		foreach(JvmConstant jc, constants)
		{
			++i;
			if(jc.type == cnst.type)
			{
				bool equal = false;
				switch(jc.type)
				{
				case INT4_VALUE:
					equal = jc.value.int4 == cnst.value.int4; break;
				case FLOAT_VALUE:
					equal = jc.value.real == cnst.value.real; break;
				case UTF8_VALUE:
					equal = *jc.value.utf8 == *cnst.value.utf8; break;
				case STRING_N:
				case CLASS_N:
					equal = jc.value.string_const == cnst.value.class_const; break;
				case NAME_AND_TYPE:
				case METHOD_REF:
				case FIELD_REF:
					equal = jc.value.name_and_type[UTF8_NAME] == cnst.value.name_and_type[UTF8_TYPE]
						 && jc.value.name_and_type[UTF8_NAME] == cnst.value.name_and_type[UTF8_TYPE];
						 break;
				}
				if(equal)
				{
					return i;
				}
			}
		}
		return -1;
	}

	/**
	* »щет константу Utf8 с заданным значением
	* @return номер константы [1...N]  или -1, если не найдено
	*/
	int searchUtf8(QString& utf8)
	{
		JvmConstant jc = { UTF8_VALUE, 0, false };
		jc.value.utf8 = &utf8;
		return searchConstant(jc);
	}

	/**
	* »щет константу  ласс с заданным именем
	* @return номер константы [1...N]  или -1, если не найдено
	*/
	int searchClass(QString& className)
	{
		int n = searchUtf8(className);
		if(n <= 0)
			return n;

		JvmConstant jc = { CLASS_N, 0, false };
		jc.value.class_const = n;
		return searchConstant(jc);
	}
};