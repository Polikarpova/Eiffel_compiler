#include <locale.h>
#include <string>

extern FILE *yyin;
int yyparse();

int main(int argc, char *argv[])
{

	//setlocale(LC_ALL, "russian");
	freopen("output.txt", "w", stdout);
	yyin = fopen("test.e", "r");
	int parse_result = yyparse();

	printf("yyparse() returned %i\n", parse_result);
}




/* TODO
	- fix *addToList*() mistakes
	- fix working with strcat() & strcpy(), literal & yylval
*/