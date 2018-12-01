#pragma once
#include "feature.h"
#include "FeatureClients.h"
#include "EiffelType.h"

class Field : public Feature
{

public:

	Field(void);
	~Field(void);

	short int	name,
				nameAndTypeConstantNumber,
				fieldrefConstantNumber;
	FeatureClients* clients;
	EiffelType* type;
};

