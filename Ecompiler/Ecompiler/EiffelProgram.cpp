#include "EiffelProgram.h"
#include "MetaClass.h"
#include "EiffelClass.h"
#include "EiffelArray.h"
#include "RTLMetaClass.h"
#include "VoidType.h"
#include "BOOLEAN.h"
#include "CHARACTER.h"

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

	if(syntaxErrorsN > 0) {
		// stop analyze
		return program;
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
	program->round3();

	if(program->errors.size() > 0) {
		// stop compilation
		return program;
	}

	// ������ 4
	program->compile(); // ����� ��� ���?

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
	EiffelType *string_type;
	EiffelType *void_type = VoidType::instance();
	IntegerType *int_type = IntegerType::instance();
	EiffelBOOLEAN* bool_type = new EiffelBOOLEAN();
	EiffelCHARACTER* char_type = new EiffelCHARACTER();
	
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


	mc = new EiffelNONE(this);
	this->classes[ mc->name() ] = mc;

	mc = new EiffelANY(this);
	fld = new Field(mc, this->findClass("CONSOLEIO")->getType(), "io");
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
	mtd->paramCount = 3; // this + 2 ���������
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