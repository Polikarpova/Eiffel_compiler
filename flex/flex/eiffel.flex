%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <conio.h>
	#include <locale.h> 

	#include "lexHelpers.h"

%}

%option noyywrap
%option never-interactive
%option yylineno

ID				[a-z][_a-z0-9]*

BOOLEAN			true|false
VOID 			void
WHITESPACE		[ \t\n\r]+

INT_16 			-?0x[0-9a-f]+
INT_10 			-?[0-9]+|0
INT_8 			-?0c[0-7]+
INT_2 			-?0b[01]+

NUM          	[0-9]+
REAL          	([0-9]*[\.]{NUM})|({NUM}[\.][0-9]*)

KEYWORD (agent|alias|all|and|and\s+then|as|assign|attribute|check|class|convert|create|Current|debug|deferred|do|else|elseif|end|ensure|expanded|export|external|feature|from|frozen|if|implies|inherit|inspect|invariant|like|local|loop|not|note|obsolete|old|once|only|or|or\s+else|Precursor|redefine|rename|require|rescue|Result|retry|select|separate|then|TUPLE|undefine|until|variant|when|xor)

%x SPECIAL_CHAR
%x SINGLE_QUOTED_CHAR
%x DOUBLE_QUOTED_STRING
%x SINGLE_LINE_COMMENT

%%

%{
	int startLine = 0;
	char literal[1000];
%}

\'								{ BEGIN(SINGLE_QUOTED_CHAR); literal[0] = '\0'; startLine = yylineno; }
<SINGLE_QUOTED_CHAR>\\n			{ strcat(literal, yytext);}
<SINGLE_QUOTED_CHAR>[^\']		{ strcat(literal, yytext);}
<SINGLE_QUOTED_CHAR>\'			{ printf("Found single quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

\"									{ BEGIN(DOUBLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
<DOUBLE_QUOTED_STRING>[^%\"]			{ strcat(literal, yytext);}
<DOUBLE_QUOTED_STRING>\"			{ printf("Found double quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%.			{ append_special_char_digraph(literal, yytext);}

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment\n"); BEGIN(INITIAL);}

":="					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"="						{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"/="					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"+" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"-" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"*" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"/"						{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"<" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"<=" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
">" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
">=" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"^" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"and" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"xor" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"or" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"not" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
and\s+then 				{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
or\s+else 				{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"implies" 				{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }

";" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"(" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
")" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"{" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"}" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"[" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"]" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
":" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"." 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"," 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"?" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"!" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"$" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }

{KEYWORD}				{ printf("Found keyword \"%s\" in line %d\n", yytext, yylineno); }
{BOOLEAN}				{ printf("Found boolean value \"%s\" in line %d\n", yytext, yylineno); }
{VOID}					{ printf("Found null-value \"%s\" in line %d\n", yytext, yylineno); }
{ID}					{ printf("Found identifier \"%s\" in line %d\n", yytext, yylineno); }

{INT_10}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext), yylineno); /*{NATURAL}	{ printf("Found unsigned int value \"%s\" in line %d\n", yytext, yylineno); }*/ }
{INT_16}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'x'), yylineno);}
{INT_8}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'c'), yylineno);}
{INT_2}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'b'), yylineno);}

{REAL}					{ printf("Found real value \"%f\" in line %d\n", yy_parse_real(yytext), yylineno); }

{WHITESPACE}			{ /* skip  {WHITESPACE} */ }
%%