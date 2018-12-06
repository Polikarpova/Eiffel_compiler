#include "CallStmt.h"


CallStmt::CallStmt(void)
{
}


CallStmt::~CallStmt(void)
{
}

/*static*/ CallStmt* CallStmt::create(Method* mtd, struct NExpr* expr) {

	bool success = false;
	CallStmt* cs = new CallStmt();

	//проверка на ошибулечки
	//if ( )

	//приписать номер к узлу константы

	//проверка соответствия количества и типов выражений

	success = true;

	return success? cs : 0;

}