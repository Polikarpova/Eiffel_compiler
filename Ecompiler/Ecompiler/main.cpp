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


// test
#include "bisontest.h"


int main(int argc, char *argv[])
{
	if(false)
	{
		BisonTest testClass(0);
		QTest::qExec(&testClass);
		return 0;
	}


	//setlocale(LC_ALL, "russian");

	//freopen("output.txt", "w", stdout);

	//char[] infile = "test.e";
	//char infile[] = "../../samples/sample.e";
	//char infile[] = "../../samples/class_creation.e";
	char infile[] = "../../samples/testclass.e";
	yyin = fopen(infile, "r");

	int parse_result = yyparse();

	fclose(yyin);

	printf("yyparse() returned %i\n", parse_result);

	printf("ROOT: %p\n", root);

	if(root && syntax_errors_logged == 0)
	{
		print2dot("tree.dot", root);
		printf("see picture\n");
		// run dot & kill current process
		execlpe("cmd", "/c", "run_dot.bat", "", 0,0,0);
	}
	else
	{
		printf("tree was not created.\n");

		printf("Error log:\n");
		for( int i=0 ; i<syntax_errors_logged ; ++i )
		{
			//printf("%d: %s\n",i,syntax_errors[i]);
			printf("%2d: ",i);
			printf("%s\n", "[error in printf()]");  // syntax_errors[i]);
		}
	}

	// `hit any key ...`
	system("pause");
}

/* TODO
	- export tree to DOT
	+ capture INHERIT clauses in classes (add to bison rules & structures)
	-~ test parsing empty class, empty features, etc
*/