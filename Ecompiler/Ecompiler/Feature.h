#pragma once
#include "tree_structs.h"
#include "MetaClass.h"
#include "EiffelType.h"

class Feature
{
public:
	Feature(void);
	~Feature(void);

	/*fields*/
	struct NFeature* tree_node;

	MetaClass* metaClass;
	QString name;
	QString descriptor;
	QSet<QString> clients;
	/** Тип поля / возвращаемое значение метода */
	EiffelType* type;

	/**getters*/
	virtual bool isMethod() = 0;
	virtual bool isField() = 0;

	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* s);
	static bool isNameConflicting(MetaClass* mc, const QString& lowerName);

	bool isExportedTo(const QString& upperName);
	void recordClients(const struct NIdList* List);
	QString createDescriptor(EiffelType* type) { return QString(""); };
};

