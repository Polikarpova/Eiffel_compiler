#include <locale.h>
#include <string>
#include "print2dot.h"

// #include <process.h>
#include <QProcess>

extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;

/* < Error handling > */
extern char** syntax_errors;
extern int syntax_errors_logged;
/* </ Error handling > */

#include "EiffelProgram.h"
#include "ByteCode.h"

// tests
#include "bisontest.h"

/*
arg[0]: -
arg[1]: input file name (no extension): fnm
	fnm.e
	fnm.dot
	fnm.png

*/

//#include "Expression.h"

int main(int argc, char *argv[])
{
	//setlocale(LC_ALL, "russian");
	//freopen("output.txt", "w", stdout);

	//Expression expr;

	if(true)
	{
		printf("Running a test for ByteCode...\n");

		ByteCode bc;
		bc.log("Begin of vakhanalia /o/");
		bc.s1(0xCA).s1(0xFE).u1(0x66).u1(0xBA).u1(0xBE);
		bc.iconst_(-1).iconst_(5);
		 ByteCode bc_1;
		 bc_1.log("Begin Of Nested ByteCode block")
			 .u2(0x0000).u4(0xCAFEBABE)
			 .log("End Of Nested ByteCode block");
		bc.append(bc_1)
			.u1(0x00).u1(-2)
			.u1(0x00).u2(-2)
			.u1(0x00).u4(-2)
			.log("End Of Whole ByteCode");

		bc.toFile("bytecode-test.bin");

		bc.printLog();

		return 0;
	}

	if(false)
	{
		BisonTest testClass(0);
		QTest::qExec(&testClass);
		return 0;
	}

	char in_fnm[100];
	char file_name[100];

	if(argc > 1)
	{
		strcpy(in_fnm, argv[1]);
	}
	else
	{
		//char[] infile = "test.e";
		//char infile[] = "../../samples/sample.e";
		//char infile[] = "../../samples/class_creation.e";
		//char infile[] = "../../samples/array_test.e";
		////char infile[] = "../../samples/testclass.e";
		//char infile[] = "../../samples/chain.e";

		//char infile[] = "../../samples/syntax/class_copy";
		char infile[] = "../../samples/bytecode/hello_world";
		strcpy(in_fnm, infile);
	}
		
	strcpy(file_name, in_fnm);
	strcat(file_name, ".e");
	
	printf("Processing file %s...\n", file_name);

	yyin = fopen(file_name, "r");
	int parse_result = yyparse();
	fclose(yyin);

	printf("yyparse() returned %i\n", parse_result);
	printf("ROOT: %p\n", root);

	if(root)
	{
		printf("first_line: %d, last_line: %d \n",root->loc.first_line, root->loc.last_line);
		strcpy(file_name, in_fnm);
		strcat(file_name, ".dot");
	
		print2dot(file_name, root);
		printf("check out tree in %s\n",file_name);


		// make semantic classes
		EiffelProgram* program = EiffelProgram::create(root, syntax_errors, syntax_errors_logged);
		
		printf("\n ====== Error List: ======\n");


		// run dot
		QProcess::startDetached(QString("cmd /C run_dot.bat %1 ../../samples/test").arg(in_fnm));
	}
	else
	{
		printf("tree was not viewed.\n");
	}

	if(argc <= 1) // debug mode
	{
		// `hit any key ...`
		system("pause");
	}
}

/* TODO
	+ case-insensitive IDs comparation
	tip. ID to store: 1st encountered variant (other entries may differ in letter case)

	+ remove semantics part from ReadMe
	+ remove flex file build step from build (turn off)
	+ apply changes in semantics DOC from 4.12.2018

	- (?^3) create ByteCode compiler class
	- ������ ������ ����������� ����� � Eiffel.classes


*/

