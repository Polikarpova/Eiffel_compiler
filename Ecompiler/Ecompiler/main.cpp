#include <locale.h>
#include <string>
#include "print2dot.h"

#include <process.h>

extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;

/* < Error handling > */
extern char** syntax_errors;
extern int syntax_errors_logged;
/* </ Error handling > */


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
		char infile[] = "../../samples/chain.e";
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
		strcpy(file_name, in_fnm);
		strcat(file_name, ".dot");
	
		print2dot(file_name, root);
		printf("see picture %s\n",file_name);
		// run dot & kill current process
		execlpe("cmd", "/c", "run_dot.bat", in_fnm, "../../samples/test", 0,0,0);
	}
	else
	{
		printf("tree was not viewed.\n");

		//printf("Error log:\n");
		//for( int i=0 ; i<syntax_errors_logged ; ++i )
		//{
		//	//printf("%d: %s\n",i,syntax_errors[i]);
		//	printf("%2d: ",i);
		//	printf("%s\n", "[error in printf()]");  // syntax_errors[i]);
		//}
	}

	if(argc <= 1) // debug mode
	{
		// `hit any key ...`
		system("pause");
	}
}

/* TODO
	+ export tree to DOT
	+ test parsing empty class, empty features, etc
*/

