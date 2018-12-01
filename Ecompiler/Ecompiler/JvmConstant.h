#pragma once
#include "enums.h"
#include <qlist.h>

struct JvmConstant
{
	enum JvmConstantType type;
	union JvmConstantValue value;
	
	bool isInvalid;
};

class ConstantTable {

public:

	ConstantTable() {};
	~ConstantTable() {};

	/** 
	* Возврашает константу по номеру n: [1...N] - номер по таблице констант
	* А если такого номера нет, то isInvalid = true
	*/
	JvmConstant get(int n); 
	
	/**
	* Добавляет константу если её нет
	* А если такая уже есть, то только возвращает её номер
	* @return номер константы в таблице : [1...N]
	*/
	int put(JvmConstant cnst);

	/*fields*/
	QList<JvmConstant> constants;
};