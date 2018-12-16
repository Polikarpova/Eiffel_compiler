#pragma once
#include "tree_structs.h"
#include "MetaClass.h"
#include "EiffelType.h"
#include "ByteCode.h"


class Feature
{
public:
	Feature(void);
	//* for RTL classes
	Feature(MetaClass* mc, EiffelType* type, const QString& name);
	~Feature(void);

	/*fields*/
	struct NFeature* tree_node;

	MetaClass* metaClass;
	QString name;
	QString descriptor;
	QSet<QString> clients;

	/** Тип поля / возвращаемое значение метода */
	EiffelType* type;
	bool isVoid() { return this->type->isVoid(); }

	/**getters*/
	virtual bool isMethod() = 0;
	virtual bool isField() = 0;
	QString getDescriptor() {if(descriptor.isEmpty()){descriptor=createDescriptor();} return descriptor; }

	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* s);
	static bool isNameConflicting(MetaClass* mc, const QString& lowerName);

	bool isExportedTo(const QString& upperName);
	bool isExportedTo(const EiffelClass* clientClass);
	
	void recordClients(const struct NIdList* List);
	virtual QString createDescriptor() { return QString(""); };
};

