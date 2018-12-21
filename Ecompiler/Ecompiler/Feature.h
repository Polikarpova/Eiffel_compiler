#pragma once
#include "tree_structs.h"
#include "MetaClass.h"
#include "EiffelType.h"
#include "ByteCode.h"

// флаги доступа
#define ACC_PUBLIC  0x0001
#define ACC_STATIC  0x0008

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
	QString javaName;
	QString descriptor;
	
	//* номера констант_UTF8 класса: имя члена класса, дескриптор члена класса 
	short int name_constN, descr_constN
		, addFlags;	//addFlags - в дополнение к флагу по умолчанию ACC_PUBLIC.
		    //Сюда можно помещать и другие флаги (напр., ACC_STATIC), для метода `public static void main(java.lang.String args[])`

	QSet<QString> clients;

	/** Тип поля / возвращаемое значение метода */
	EiffelType* type;
	bool isVoid() { return this->type->isVoid(); }

	/**getters*/
	virtual bool isMethod() = 0;
	virtual bool isField() = 0;

	QString getDescriptor() {if(descriptor.isEmpty()){descriptor=createDescriptor();} return descriptor; }
	virtual void initJavaName();

	/*methods*/
	static bool create(MetaClass* mc, struct NFeature* s);
	static bool isNameConflicting(MetaClass* mc, const QString& lowerName);

	bool isExportedTo(const QString& upperName);
	bool isExportedTo(MetaClass* clientClass);
	
	void recordClients(const struct NIdList* List);
	virtual QString createDescriptor() { return QString("!"); };

	//* создать константы в классе: имя и дескриптор
	void initConstants();

};

