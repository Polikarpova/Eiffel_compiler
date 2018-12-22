#pragma once
#include <qset.h>
#include <qmap.h>

#include <tree_structs.h>
#include <QString>

//#include "MetaClass.h"
class MetaClass;
class Method;
class MethodCall;
class Expression;

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

	/*methods*/
	int logError(QString type, QString message,	int line);
	void printErrors();

	/** \return NULL if no class found */
	MetaClass* findClass(const QString& upperName);

	//* ����� ������-�������
	MethodCall* callHelper(Method* context_mtd, QString helperName, QList<Expression*> arguments = QList<Expression*>() );

	/** ������ 2 */
	bool round2();
	/** ������ 3 */
	bool round3();
	/** ������ 4 */
	bool round4();
	/** ���������� */
	bool compile();

	void createRTL();

	/*functions*/
	static EiffelProgram* currentProgram;
	static EiffelProgram* create(struct NClassList* root, char** syntaxErrors = 0, int syntaxErrorsN = 0);

};
