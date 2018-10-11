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

TRUE			true
FALSE			false
VOID 			void
WHITESPACE		[ \t\n\r]

D2          	[01]
D_2				[_01]
D8          	[0-7]
D_8          	[_0-7]
D10          	[0-9]
D_10          	[_0-9]
D16				[0-9a-f]
D_16			[_0-9a-f]

INT_16 			0x({D16}{D_16}*)?{D16}
INT_10 			  ({D10}{D_10}*)?{D10}
INT_8 			0c({D8}{D_8}*)?{D8}
INT_2 			0b({D2}{D_2}*)?{D2}

NUM          	[0-9]+
REAL_0          (([0-9]*[\.]{NUM})|({NUM}[\.][0-9]*))
REAL          	((({INT_10})?[\.]{INT_10})|({INT_10}[\.]({INT_10})?))
EXPONENT	 	(({INT_10}|{REAL})e[+-]?{NUM})

KEYWORD ()


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
<SINGLE_QUOTED_CHAR>[^\']		{ strcat(literal, yytext); }
<SINGLE_QUOTED_CHAR>\'			{ if(strlen(literal) == 1) {printf("Found single quoted literal \'%c\'. From line %d to line %d\n", literal[0], startLine, yylineno); } else {
 printf("Invalid single quoted literal \'%s\' at line %d\n", literal, yylineno); }
 BEGIN(INITIAL); }

\"									{ BEGIN(DOUBLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
<DOUBLE_QUOTED_STRING>[^%\"]			{ strcat(literal, yytext);}
<DOUBLE_QUOTED_STRING>\"			{ printf("Found double quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%\/[0-9]{1,3}\/	{ append_special_char_by_code(literal, yytext);}
<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%.			{ append_special_char_digraph(literal, yytext);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING><<EOF>>	{ printf("Unterminated string or char literal at line %d\n", yylineno);  BEGIN(INITIAL);}

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment\n"); BEGIN(INITIAL);}

":="					{ printf("Found operator \"%s\" in line %d\n", "ASSIGN", yylineno); }
"="						{ printf("Found operator \"%s\" in line %d\n", "EQUALS", yylineno); }
"/="					{ printf("Found operator \"%s\" in line %d\n", "NOT_EQUALS", yylineno); }
"<" 					{ printf("Found operator \"%s\" in line %d\n", "LESS", yylineno); }
"<=" 					{ printf("Found operator \"%s\" in line %d\n", "LESS_OR_EQUAL", yylineno); }
">" 					{ printf("Found operator \"%s\" in line %d\n", "GREATER", yylineno); }
">=" 					{ printf("Found operator \"%s\" in line %d\n", "GREATER_OR_EQUAL", yylineno); }
"and" 					{ printf("Found operator \"%s\" in line %d\n", "AND", yylineno); }
"xor" 					{ printf("Found operator \"%s\" in line %d\n", "XOR", yylineno); }
"or" 					{ printf("Found operator \"%s\" in line %d\n", "OR", yylineno); }
"not" 					{ printf("Found operator \"%s\" in line %d\n", "NOT", yylineno); }
and{WHITESPACE}+then 	{ printf("Found operator \"%s\" in line %d\n", "AND_THEN", yylineno); }
or{WHITESPACE}+else 	{ printf("Found operator \"%s\" in line %d\n", "OR_ELSE", yylineno); }
"implies" 				{ printf("Found operator \"%s\" in line %d\n", "IMPLIES", yylineno); }
"//"					{ printf("Found operator \"%s\" in line %d\n", "DIV", yylineno); }
"\\"					{ printf("Found operator \"%s\" in line %d\n", "MOD", yylineno); }

"+" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"-" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"*" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"/"						{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"^" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
";" 					{ printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }

"(" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
")" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"{" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"}" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
":" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"." 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"," 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }

"all" 					{ printf("Found keyword \"%s\" in line %d\n", "ALL", yylineno); }
"class" 				{ printf("Found keyword \"%s\" in line %d\n", "CLASS", yylineno); }
"create" 				{ printf("Found keyword \"%s\" in line %d\n", "CREATE", yylineno); }
"Current" 				{ printf("Found keyword \"%s\" in line %d\n", "CURRENT", yylineno); }
"do" 					{ printf("Found keyword \"%s\" in line %d\n", "DO", yylineno); }
"else" 					{ printf("Found keyword \"%s\" in line %d\n", "ELSE", yylineno); }
"elseif" 				{ printf("Found keyword \"%s\" in line %d\n", "ELSEIF", yylineno); }
"end" 					{ printf("Found keyword \"%s\" in line %d\n", "END", yylineno); }
"feature" 				{ printf("Found keyword \"%s\" in line %d\n", "FEATURE", yylineno); }
"from" 					{ printf("Found keyword \"%s\" in line %d\n", "FROM", yylineno); }
"if" 					{ printf("Found keyword \"%s\" in line %d\n", "IF", yylineno); }
"inherit" 				{ printf("Found keyword \"%s\" in line %d\n", "INHERIT", yylineno); }
"local" 				{ printf("Found keyword \"%s\" in line %d\n", "LOCAL", yylineno); }
"loop" 					{ printf("Found keyword \"%s\" in line %d\n", "LOOP", yylineno); }
"note" 					{ printf("Found keyword \"%s\" in line %d\n", "NOTE", yylineno); }
"Precursor" 			{ printf("Found keyword \"%s\" in line %d\n", "PRECURSOR", yylineno); }
"redefine" 				{ printf("Found keyword \"%s\" in line %d\n", "REDEFINE", yylineno); }
"rename" 				{ printf("Found keyword \"%s\" in line %d\n", "RENAME", yylineno); }
"Result" 				{ printf("Found keyword \"%s\" in line %d\n", "RESULT", yylineno); }
"select" 				{ printf("Found keyword \"%s\" in line %d\n", "SELECT", yylineno); }
"then" 					{ printf("Found keyword \"%s\" in line %d\n", "THEN", yylineno); }
"undefine" 				{ printf("Found keyword \"%s\" in line %d\n", "UNDEFINE", yylineno); }
"until" 				{ printf("Found keyword \"%s\" in line %d\n", "UNTIL", yylineno); }

{TRUE}					{ printf("Found boolean value \"%d\" in line %d\n", true, yylineno); }
{FALSE}					{ printf("Found boolean value \"%d\" in line %d\n", false, yylineno); }
{VOID}					{ printf("Found null-value \"%s\" in line %d\n", "<void>", yylineno); }
{ID}					{ printf("Found identifier \"%s\" in line %d\n", yytext, yylineno); }

{EXPONENT}				{ printf("Found exponent value \"%e\" in line %d\n", yy_parse_real(yytext), yylineno); }
{INT_10}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext), yylineno); /*{NATURAL}	{ printf("Found unsigned int value \"%s\" in line %d\n", yytext, yylineno); }*/ }
{INT_16}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'x'), yylineno);}
{INT_8}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'c'), yylineno);}
{INT_2}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'b'), yylineno);}

{REAL}[^.]				{ printf("Found real value \"%f\" in line %d\n", yy_parse_real(yytext), yylineno);}

{WHITESPACE}+			{ /* skip  {WHITESPACE} */ }

<*>.					{ printf("Unexpected char \'%c\' encountered at line %d\n", yytext, yylineno);  BEGIN(INITIAL);}
%%