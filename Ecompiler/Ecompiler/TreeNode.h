#pragma once
#include "tree_structs.h"

class ByteCode;

class TreeNode {

public:
	TreeNode() {};
	~TreeNode() {};

	/*methods*/
	virtual ByteCode& toByteCode(ByteCode &) = 0;

	/*fields*/
	//Struct* pStruct;
};