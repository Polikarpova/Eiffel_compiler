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
	* ���������� ��������� �� ������ n: [1...N] - ����� �� ������� ��������
	* � ���� ������ ������ ���, �� isInvalid = true
	*/
	JvmConstant get(int n); 
	
	/**
	* ��������� ��������� ���� � ���
	* � ���� ����� ��� ����, �� ������ ���������� � �����
	* @return ����� ��������� � ������� : [1...N]
	*/
	int put(JvmConstant cnst);

	/*fields*/
	QList<JvmConstant> constants;
};