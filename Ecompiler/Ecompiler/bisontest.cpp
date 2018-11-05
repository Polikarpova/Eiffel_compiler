#include "bisontest.h"


// bison includes
#include "print2dot.h"
extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;


BisonTest::BisonTest(QObject *parent)
	: QObject(parent)
{

}

BisonTest::~BisonTest()
{

}


void BisonTest::emptyClass()
{
	char infile[] = "../../samples/syntax/class_empty.e";
	yyin = fopen(infile, "r");

	int parse_result = yyparse();

	fclose(yyin);

	QCOMPARE(parse_result, 0);

}
