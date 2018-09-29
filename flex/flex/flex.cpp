// flex.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include "lex.yy.c"
#include "eiffel.flex.c"
#include <locale.h>
#include <string>


void _tmain(int argc, _TCHAR* argv[])
{
	//setlocale(LC_ALL, "russian");
	freopen("output.txt", "w", stdout);
	yyin = fopen("test.e", "r");
	yylex();
}



/* TODO
	- underscores in numeric constants
		-fix!

*/