#pragma once
#include <qset.h>
#include <qmap.h>

#include <tree_structs.h>

//#include "MetaClass.h"
class MetaClass;

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
	
	QList<CompilerError> errors;

	int logError(QString type, QString message,	int line)
	{
		CompilerError ce = {type,message,line};
		errors.push_back(ce);
		return errors.size();
	}

	static EiffelProgram* create(struct NClassList* root, char** syntaxErrors = 0, int syntaxErrorsN = 0);
	static EiffelProgram* currentProgram;
};