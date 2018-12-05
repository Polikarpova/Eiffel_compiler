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

	QString name;
	QString descriptor;
	QSet<QString> clients;
	/** Тип поля / возвращаемое значение метода */
	EiffelType* type;


	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* s);

	void recordClients(const struct NIdList* List);
	QString createDescriptor() { return QString(""); };

};

