#include "EiffelProgram.h"
#include "MetaClass.h"
#include "RTLMetaClass.h"

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

	// ������ 1
	// add RTL classes
	program->createRTL();

	// iterate user classes
	for(struct NClass* i = List->first ;  ; i = i->next )
	{
		MetaClass::create(i);
		if(i == List->last) break;
	}

	// ������ 2
	program->round2();

	// ������ 3
	//program->round3();

	// ������ 4
	//program->compile(); // ����� ��� ���?

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
	foreach(MetaClass* mc, this->classes)
	{
		if(mc->tree_node == NULL)
			continue; // RTL class

		mc->generateCode();
	}

	return true;
}


void EiffelProgram::createRTL()
{
	MetaClass* mc;

	mc = new EiffelNONE(this);
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;

	mc = new EiffelANY(this);
	mc->tree_node = NULL;
	Field* f_io = new Field();
	f_io->name = "io";
	f_io->type = mc->getType();
	f_io->recordClients(NULL); // set ANY as client
	mc->fields[ f_io->name ] = f_io;
	this->classes[ mc->name() ] = mc;

	mc = new EiffelSTRING(this);
	mc->tree_node = NULL;
	this->classes[ mc->name() ] = mc;

	// IO class
	mc = new RTLMetaClass(this, QString("CONSOLEIO"));
	mc->tree_node = NULL;
	//mc->isStatic = true; // this allows LocalVariableRef to refer the class as variable
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