#pragma once
#include <qset.h>

class FeatureClients {

public:
	enum {	
			ANY,
			NONE,
			CLASSES
		 } mode;

	//QSet<EiffelClass*> clients; //������ ������� - �������� ����� ������ (feature)
};