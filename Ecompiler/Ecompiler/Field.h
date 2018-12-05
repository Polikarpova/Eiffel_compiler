#pragma once
#include "feature.h"
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
	QSet<QString> clients;
	EiffelType* type;
};

