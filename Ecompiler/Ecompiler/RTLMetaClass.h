#pragma once
#include "MetaClass.h"
#include "EiffelType.h"


class RTLMetaClass : public MetaClass
{

public:
	
	RTLMetaClass(void);
	RTLMetaClass(EiffelProgram* program, const QString& name);
	~RTLMetaClass(void);

	/*methods*/
	virtual const QString& name() { return _name; }
	QString javaPackage() {return QString("rtl");}


	/*fields*/
};

// ячдю янахпюел бяе RTL-ЙКЮЯЯШ дкъ ондйкчвемхъ й опнцпюллле бяецн кхьэ ндмнцн RTLMetaClass.h

#include "VoidType.h"
#include "EiffelNONE.h"
#include "EiffelANY.h"
#include "EiffelSTRING.h"
#include "IntegerType.h"

