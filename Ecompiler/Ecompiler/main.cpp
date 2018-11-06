#include <locale.h>
#include <string>
#include "print2dot.h"

#include <process.h>

extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;

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

	if(root)
	{
		print2dot("tree.dot", root);
		printf("see picture\n");
		// run dot & kill current process
		execlpe("cmd", "/c", "run_dot.bat", "", 0,0,0);
	}
	else
	{
		printf("tree was not created.\n");
	}

	// `hit any key ...`
	system("pause");
}

/* TODO
	- export tree to DOT
	+ capture INHERIT clauses in classes (add to bison rules & structures)
	+ refactor NRef as hierarchy of '.' operations not as RefList (as is now)
	-~ test parsing empty class, empty features, etc
*/