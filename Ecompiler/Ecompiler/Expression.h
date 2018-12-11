#pragma once
#include "TreeNode.h"
#include "EiffelType.h"

class Method;

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	Method* currentMethod;

	/*methods*/
	static Expression* create(Method* mtd, struct NExpr* s);
	
	//перегружается в дочерних классах
	virtual bool isLeftValue() { return this->_isLeftValue; };

	//возвращает тип возвращаемый выражением
	//2+2 вернет INTEGER
	EiffelType* expressionType(){ return type; }


	/*fields*/
	struct NExpr* tree_node;

	bool _isLeftValue;

	Expression* left;
	Expression* right;
	EiffelType* type;	//(?)тип возвращаемого значения

};