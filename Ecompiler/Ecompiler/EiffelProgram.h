#pragma once
#include "MetaClass.h"
#include <qset.h>

class EiffelProgram {

public:
	EiffelProgram(void);
	~EiffelProgram(void);

	QMap<QString, MetaClass*> clients;

	//QSet<FeatureClients*> clients; //������ ������� - �������� ����� ������ (feature)
};