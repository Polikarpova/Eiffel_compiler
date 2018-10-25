#include <locale.h>
#include <string>

#include <process.h>

extern FILE *yyin;
extern int yyparse();
extern struct NClassList* root;

void print2dot(char* filename, struct NClassList* root);


int main(int argc, char *argv[])
{

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
		execlpe("cmd", "/c", "run_dot.bat", "", 0,0,0);
		printf("see picture\n");
	}
}




/* TODO
	+ fix *addToList*() mistakes
	- fix working with strcat() & strcpy(), literal & yylval
*/