#pragma once
#include "MetaClass.h"
#include <qset.h>

#include <tree_structs.h>
#include "FeatureClients.h"

struct CompilerError
{
	QString type, message;
	int line; // -1 : unknown line
};

class EiffelProgram {

public:
	EiffelProgram(void);
	~EiffelProgram(void);

	QMap<QString, MetaClass*> classes;

	//! список классов - клиентов члена класса (feature)
	QSet<FeatureClients*> clients;
	
	QList<CompilerError> errors;

	static EiffelProgram* create(struct NClassList* root, char** syntaxErrors = 0, int syntaxErrorsN = 0);
};