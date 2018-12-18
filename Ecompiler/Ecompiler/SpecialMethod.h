#include "Method.h"

/* usage of this .h:
#include "SpecialMethod.h"
*/

#include "ByteCode.h"


/** Метод с непосредственным доступом к байт-коду (извне)
*/
class SpecialMethod : public Method
{

public:

	SpecialMethod(void);
	//* for RTL classes
	SpecialMethod(MetaClass* mc, EiffelType* type, const QString& name, QList<LocalVariable> argList = QList<LocalVariable>() )
		: Method(mc, type, name, argList) {};
	~SpecialMethod(void);

	/*fields*/
	ByteCode bytecode;

	/*methods*/
	virtual ByteCode& generateCode4Body(ByteCode &bc) { return bc.append(bytecode); }

};