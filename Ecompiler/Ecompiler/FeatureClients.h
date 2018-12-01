#pragma once
#include <qset.h>
#include "EiffelClass.h"

class FeatureClients {

public:
	enum {	
			ANY,
			NONE,
			CLASSES
		 } mode;

	QSet<EiffelClass*> clients; //список классов - клиентов члена класса (feature)
};