#pragma once
#include "MetaClass.h"
#include "EiffelType.h"


class RTLMetaClass : public MetaClass
{

public:
	
	RTLMetaClass(void);
	RTLMetaClass(EiffelProgram* program, const QString& name) {
		this->program = program;
		this->parent = NULL;
		this->isAbstract = false;
		this->_exprType = NULL;

		this->_name = name;
	};
	~RTLMetaClass(void);

	/*methods*/
	virtual const QString& name() { return _name; }
	QString javaPackage() {return QString("rtl");}


	/*fields*/

	//* ОПНЯРНЕ ХЛЪ ЙКЮЯЯЮ
	QString _name;
};

// ячдю янахпюел бяе RTL-ЙКЮЯЯШ дкъ ондйкчвемхъ й опнцпюллле бяецн кхьэ ндмнцн RTLMetaClass.h

#include "EiffelNONE.h"
#include "EiffelANY.h"
#include "EiffelSTRING.h"
#include "INTEGER.h"

