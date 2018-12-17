#include "EiffelProgram.h"
#include "MetaClass.h"
#include "EiffelClass.h"
#include "RTLMetaClass.h"
#include "VoidType.h"

#include "Field.h"
#include "Method.h"

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

	// опнунд 1
	// add RTL classes
	program->createRTL();

	// iterate user classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass::create(i);
		if(i == List->last) break;
	}

	// опнунд 2
	program->round2();

	// опнунд 3
	program->round3();

	// опнунд 4
	program->compile(); // ГДЕЯЭ ХКХ МЕР?

	return program;
}

MetaClass* EiffelProgram::findClass(const QString& upperName)
{
	return classes.value(upperName, NULL);
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
	EiffelClass *string_type;
	EiffelType *void_type = new VoidType();

	// VOID class
	mc = new RTLMetaClass(this, QString("VOID"));
	this->classes[ mc->name() ] = mc;

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
	this->classes[ mc->name() ] = mc;

	mc = new EiffelNONE(this);
	this->classes[ mc->name() ] = mc;

	mc = new EiffelANY(this);
	fld = new Field(mc, this->findClass("CONSOLEIO")->getType(), "io");
	mc->fields[ fld->name ] = fld;
	this->classes[ mc->name() ] = mc;
}


void EiffelProgram::printErrors()
{
	foreach(CompilerError ce, this->errors)
	{
		QString print_str = QString("%1 error%3: %2.")
			.arg(ce.type,ce.message)
			.arg(ce.line<0 ?
				("") :
				(QString(" at line %1").arg(ce.line))
				);
		wprintf(L"%s\n",print_str.data());
	}
}