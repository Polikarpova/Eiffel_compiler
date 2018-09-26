%{
	#include <math.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <conio.h>
	#include <locale.h> 
%}

%option noyywrap
%option never-interactive
%option yylineno

ID				[a-zA-Z][_a-zA-Z0-9]*
TRUE 			[tT][rR][uU][eE]
FALSE 			[fF][Aa][lL][sS][eE]
VOID 			[Vv][Oo][Ii][Dd]

INTENGER		[1-9][0-9]*|0

NUM          	[0-9]+
REAL          	([0-9]*[\.]{NUM})|({NUM}[\.][0-9]*)

KEYWORD (agent|alias|all|as|assign|attribute|check|class|convert|create|Current|debug|deferred|do|else|elseif|end|ensure|expanded|export|external|feature|from|frozen|if|implies|inherit|inspect|invariant|like|local|loop|not|note|obsolete|old|once|only|Precursor|redefine|rename|require|rescue|Result|retry|select|separate|then|TUPLE|undefine|until|variant|when)

%x SINGLE_QUOTED_STRING

%%

%{
	int startLine = 0;
	char literal[10000];
%}

\'									{ BEGIN(SINGLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
<SINGLE_QUOTED_STRING>\\n			{ strcat(literal, yytext);}
<SINGLE_QUOTED_STRING>\\\\			{ strcat(literal, "\\");}
<SINGLE_QUOTED_STRING>\\\'			{ strcat(literal, "\'");}
<SINGLE_QUOTED_STRING>[^\'\\n]		{ strcat(literal, yytext);}
<SINGLE_QUOTED_STRING>\'			{ printf("Founded single quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

{KEYWORD}				{ printf("Founded keyword \"%s\" in line %d\n", yytext, yylineno); }

":="					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"="						{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"/="					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"+" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"-" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"*" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"/"						{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"<" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"<=" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
">" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
">=" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"^" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"and" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"xor" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }
"or" 					{ printf("Founded operator \"%s\" in line %d\n", yytext, yylineno); }

";" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"(" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
")" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"{" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"}" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"[" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"]" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
":" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"." 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"," 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"?" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"!" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
\' 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
\" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
"$" 					{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }

%%