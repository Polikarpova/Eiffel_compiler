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

KEYWORD (agent|alias|all|and|and{WHITESPACE}+then|as|assign|attribute|check|class|convert|create|Current|debug|deferred|do|else|elseif|end|ensure|expanded|export|external|feature|from|frozen|if|implies|inherit|inspect|invariant|like|local|loop|not|note|obsolete|old|once|only|or|or{WHITESPACE}+else|Precursor|redefine|rename|require|rescue|Result|retry|select|separate|then|TUPLE|undefine|until|variant|when|xor)


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

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%\/[0-9]{1,3}\/	{ append_special_char_by_code(literal, yytext);}
<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%.			{ append_special_char_digraph(literal, yytext);}

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment\n"); BEGIN(INITIAL);}

":="					{ printf("Found operator \"%s\" in line %d\n", "ASSIGN", yylineno); }
"="						{ printf("Found operator \"%s\" in line %d\n", "EQUALS", yylineno); }
"/="					{ printf("Found operator \"%s\" in line %d\n", "NOT_EQUALS", yylineno); }
"~"						{ printf("Found operator \"%s\" in line %d\n", "BIT_EQUALS", yylineno); }
"/~"					{ printf("Found operator \"%s\" in line %d\n", "BIT_NOT_EQUALS", yylineno); }
"|..|"					{ printf("Found operator \"%s\" in line %d\n", "INT_INTERVAL", yylineno); }
\.\.					{ printf("Found operator \"%s\" in line %d\n", "CHAR_INTERVAL", yylineno); }
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

{EXPONENT}				{ printf("Found exponent value \"%e\" in line %d\n", yy_parse_real(yytext), yylineno); }
{INT_10}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext), yylineno); /*{NATURAL}	{ printf("Found unsigned int value \"%s\" in line %d\n", yytext, yylineno); }*/ }
{INT_16}				{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'x'), yylineno);}
{INT_8}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'c'), yylineno);}
{INT_2}					{ printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'b'), yylineno);}

{REAL}					{ 
							register int c = yyinput();	//взяли следующий символ
							
							if ( c == '.')
							{
								parse_char_interval(yytext, c);
								printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext), yylineno);
								printf("Found operator \"%s\" in line %d\n", "CHAR_INTERVAL", yylineno);
							}
							else
							{
								parse_char_interval(yytext, c);
								printf("Found real value \"%f\" in line %d\n", yy_parse_real(yytext), yylineno);
							}
						}

{WHITESPACE}+			{ /* skip  {WHITESPACE} */ }
%%