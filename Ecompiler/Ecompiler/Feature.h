#pragma once
#include "tree_structs.h"
#include "MetaClass.h"
#include "EiffelType.h"

class Feature
{
public:
	Feature(void);
	~Feature(void);

	/*fields*/
	QString name;
	QString descriptor;
	QSet<QString> clients;
	/** Тип поля / возвращаемое значение метода */
	EiffelType* type;


	static bool create(MetaClass* mc, struct NFeature* s);
};

