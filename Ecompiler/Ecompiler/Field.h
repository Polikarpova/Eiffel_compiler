#pragma once
#include "Feature.h"
#include "EiffelType.h"
#include "qset.h"

class Field : public Feature
{

public:

	Field(void);
	~Field(void);

	short int	name_constN,
				nameAndType_constN,
				fieldref_constN;
	QString descriptor;
	QSet<QString> clients;
	EiffelType* type;

	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* node);
};

