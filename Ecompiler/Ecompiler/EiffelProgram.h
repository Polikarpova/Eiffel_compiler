#pragma once
#include "MetaClass.h"
#include <qset.h>
#include "FeatureClients.h"

class EiffelProgram {

public:
	EiffelProgram(void);
	~EiffelProgram(void);

	QMap<QString, MetaClass*> classes;

	QSet<FeatureClients*> clients; //список классов - клиентов члена класса (feature)
};