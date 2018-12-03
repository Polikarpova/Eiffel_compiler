#pragma once
#include "MetaClass.h"
#include <qset.h>

#include <tree_structs.h>
#include "FeatureClients.h"

class EiffelProgram {

public:
	EiffelProgram(void);
	~EiffelProgram(void);

	QMap<QString, MetaClass*> classes;

	QSet<FeatureClients*> clients; //������ ������� - �������� ����� ������ (feature)

	static EiffelProgram* create(struct NClassList* root);
};