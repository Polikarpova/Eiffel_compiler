#pragma once
#include "TreeNode.h"
#include "EiffelType.h"
#include "ByteCode.h"

class Method;

class Expression : public TreeNode
{

public:
	
	Expression(void);
	~Expression(void);

	Method* currentMethod;

	/*methods*/
	static Expression* create(Method* mtd, struct NExpr* s);
	
	//перегружаетс€ в дочерних классах
	virtual bool isLeftValue() { return this->_isLeftValue; };
	
	/** «адать величину справа от равно.
		≈сли ¬ыражение не позвол€ет этого
		сделать, вернЄтс€ false.
	*/
	virtual bool setRightValue(Expression* r) { return false; };

	//необходим
	//возвращает тип возвращаемый выражением
	//2+2 вернет INTEGER
	EiffelType* expressionType();

	/*fields*/
	struct NExpr* tree_node;

	bool _isLeftValue;

	Expression* left;
	Expression* right;
	EiffelType* type;	//тип возвращаемого значени€

	virtual ByteCode& toByteCode(ByteCode &bc) {return bc.log("/!\\ expr -> code not implemented!.."); };


private:
	EiffelType* getReturnType();
};