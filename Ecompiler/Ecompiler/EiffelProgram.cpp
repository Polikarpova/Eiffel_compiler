#include "EiffelProgram.h"
#include "MetaClass.h"
#include "EiffelClass.h"
#include "EiffelArray.h"
#include "RTLMetaClass.h"
#include "VoidType.h"
#include "BOOLEAN.h"
#include "CHARACTER.h"
#include "REAL.h"

#include "Field.h"
#include "FieldRef.h"
#include "Method.h"
#include "MethodCall.h"

/*static*/ EiffelProgram* EiffelProgram::currentProgram = NULL;

EiffelProgram::EiffelProgram(void)
{
}


EiffelProgram::~EiffelProgram(void)
{
	classes.clear();
}


/*static*/ EiffelProgram* EiffelProgram::create(struct NClassList* List, char** syntaxErrors/* = 0*/, int syntaxErrorsN/* = 0*/)
{
	EiffelProgram* program = new EiffelProgram();
	EiffelProgram::currentProgram = program;

	// iterate existing errors
	if(syntaxErrors && syntaxErrorsN)
	{
		for(int i=0 ; i<syntaxErrorsN ; ++i)
		{
			program->logError(QString::fromUtf8("syntax"), QString::fromUtf8(syntaxErrors[i]), -1);
		}
	}

	if(syntaxErrorsN > 0) {
		// stop analyze
		return program;
	}

	// ÏÐÎÕÎÄ 1
	// add RTL classes
	program->createRTL();

	// iterate user classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass::create(i);
		if(i == List->last) break;
	}

	// ÏÐÎÕÎÄ 2
	program->round2();

	// ÏÐÎÕÎÄ 3
	program->round3();

	if(program->errors.size() > 0) {
		// stop compilation
		return program;
	}

	// ÏÐÎÕÎÄ 4
	program->compile(); // çäåñü èëè íåò?

	return program;
}

MetaClass* EiffelProgram::findClass(const QString& upperName)
{
	return classes.value(upperName, NULL);
}

MethodCall* EiffelProgram::callHelper(Method* context_mtd, QString helperName, QList<Expression*> arguments/* = QList<Expression*>() */)
{
	MetaClass *any = this->findClass("ANY");
	MetaClass *mc = this->findClass("Helper");

	// find $helper
	Field* helper_field = any->findField("$helper");

	FieldRef* helper_ref = FieldRef::create(context_mtd, helper_field);

	// find $helper
	Method* helper_mtd = mc->findMethod(helperName);

	if( ! helper_mtd ) {
		helper_mtd = 0; // !!!
	}

	// make call
	MethodCall* helper_call = MethodCall::create(context_mtd, helper_mtd, arguments, helper_ref);

	return helper_call;
}

	
bool EiffelProgram::round2()
{
	// QMap<QString, MetaClass*> classes;
	 
	foreach(MetaClass* mc, this->classes)
	{
		if(mc->tree_node == NULL)
			continue; // RTL class

		mc->createFeatures();
	}

	return true;
}
bool EiffelProgram::round3()
{
	foreach(MetaClass* mc, this->classes)
	{
		if(mc->tree_node == NULL)
			continue; // RTL class

		mc->round3();
	}

	// set class `NONE` as child of all `leaf`-classes


	return true;
}

bool EiffelProgram::compile()
{
	QDir out_dir;
	out_dir.mkpath("out");
	out_dir.cd("out");

	foreach(MetaClass* mc, this->classes)
	{
		if(mc->tree_node == NULL)
			continue; // RTL class

		mc->generateCode(out_dir);
	}

	return true;
}


void EiffelProgram::createRTL()
{
	MetaClass *mc, *string_mc;
	Method* mtd;
	Field* fld;
	EiffelType *string_type;
	EiffelType *void_type = VoidType::instance();
	IntegerType *int_type = IntegerType::instance();
	EiffelBOOLEAN* bool_type = new EiffelBOOLEAN();
	EiffelCHARACTER* char_type = new EiffelCHARACTER();
	EiffelREAL* real_type = EiffelREAL::instance();
	
	// VOID class
	mc = new RTLMetaClass(this, QString("VOID"));
	this->classes[ mc->name() ] = mc;

	// BOOLEAN class
	this->classes[ bool_type->name() ] = bool_type;
	bool_type->setType(bool_type);
	
	// CHARACTER class
	this->classes[ char_type->name() ] = char_type;
	char_type->setType(char_type);

	// IntegerType class
	this->classes[ int_type->name() ] = int_type;

	// REAL class
	this->classes[ real_type->name() ] = real_type;

	// STRING class
	mc = new EiffelSTRING(this);
	this->classes[ mc->name() ] = mc;
	string_mc = mc;
	string_type = string_mc->getType();

	// IO class
	mc = new RTLMetaClass(this, QString("CONSOLEIO"));
	mtd = new Method(mc, void_type, "put_string",
		QList<LocalVariable>() << LocalVariable(string_type, "v")
		);
	mc->methods[ mtd->name ] = mtd;
	mtd = new Method(mc, void_type, "put_integer",
		QList<LocalVariable>() << LocalVariable(int_type, "v")
		);
	mc->methods[ mtd->name ] = mtd;
	mtd = new Method(mc, void_type, "new_line");
	mc->methods[ mtd->name ] = mtd;
	this->classes[ mc->name() ] = mc;


	// Helper class
	mc = new RTLMetaClass(this, QString("Helper"));
	mtd = new Method(mc, int_type, "powerI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;
	
	mtd = new Method(mc, string_type, "addS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "equalI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "equalF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "equalS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "notEqualI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "notEqualF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "notEqualS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessOrEqualI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessOrEqualF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "lessOrEqualS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterOrEqualI",
		QList<LocalVariable>() 
		<< LocalVariable(int_type, "left") 
		<< LocalVariable(int_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterOrEqualF",
		QList<LocalVariable>() 
		<< LocalVariable(real_type, "left") 
		<< LocalVariable(real_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "greaterOrEqualS",
		QList<LocalVariable>() 
		<< LocalVariable(string_type, "left") 
		<< LocalVariable(string_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "or",
		QList<LocalVariable>() 
		<< LocalVariable(bool_type, "left") 
		<< LocalVariable(bool_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "xor",
		QList<LocalVariable>() 
		<< LocalVariable(bool_type, "left") 
		<< LocalVariable(bool_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "and",
		QList<LocalVariable>() 
		<< LocalVariable(bool_type, "left") 
		<< LocalVariable(bool_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	mtd = new Method(mc, bool_type, "implies",
		QList<LocalVariable>() 
		<< LocalVariable(bool_type, "left") 
		<< LocalVariable(bool_type, "right")
		);
	mc->methods[ mtd->name ] = mtd;

	this->classes[ mc->name() ] = mc;

	// NONE
	mc = new EiffelNONE(this);
	this->classes[ mc->name() ] = mc;


	// ANY
	mc = new EiffelANY(this);
	fld = new Field(mc, this->findClass("CONSOLEIO")->getType(), "io");
	mc->fields[ fld->name ] = fld;
	fld = new Field(mc, this->findClass("Helper")->getType(), "$helper");
	mc->fields[ fld->name ] = fld;
	this->classes[ mc->name() ] = mc;


	// ARRAY class
	mc = new RTLMetaClass(this, QString("ARRAY"));
	// type
	mc->setType(new EiffelArray( /*element=*/ this->findClass("ANY")->getType() ));
	// `make`: setup auto-created constructor
	mtd = mc->findDefaultConstructor();
	mtd->isCreator = true; // set again to be sure
	mtd->localVariables["lower"] = new LocalVariable("lower", 1, int_type);
	mtd->localVariables["upper"] = new LocalVariable("upper", 2, int_type);
	mtd->paramCount = 3; // this + 2 ïàðàìåòðà
	mtd->name = "make";
	mtd->descriptor.clear(); // reset if been created
	mc->methods[ mtd->name ] = mtd;
	// `length`: size of array
	fld = new Field(mc, int_type, "count");
	fld->isReadOnly = true;
	fld->javaName = "length";
	fld->descriptor.clear(); // reset if been created
	mc->fields[ fld->name ] = fld;
	this->classes[ mc->name() ] = mc;


}

int EiffelProgram::logError(QString type, QString message,	int line)
{
	CompilerError ce = {type,message,line};
	errors.push_back(ce);
	qDebug("%d: %s", line, message.toLocal8Bit().data());
	return errors.size();
}

void EiffelProgram::printErrors()
{
	foreach(CompilerError ce, this->errors)
	{
		QString print_str = QString("%1 error%3: %2")
			.arg(ce.type,ce.message)
			.arg(ce.line<0 ?
				("") :
				(QString(" at line %1").arg(ce.line))
				);
		wprintf(L"%s\n",print_str.data());
	}
}