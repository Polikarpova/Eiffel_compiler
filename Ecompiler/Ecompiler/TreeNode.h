#pragma once
#include "tree_structs.h"

class ByteCode;

class TreeNode {

public:
	TreeNode() {};
	~TreeNode() {};

	/*methods*/
	ByteCode& toByteCode();

	/*fields*/
	//Struct* pStruct;
};