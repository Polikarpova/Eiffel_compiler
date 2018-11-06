%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <conio.h>
	#include <locale.h> 

	#include "lexHelpers.h"
	#include "eiffel_bison.tab.h"

extern int global_LF_enabled;
%}

%option noyywrap
%option never-interactive
%option yylineno

ID				[a-z][_a-z0-9]*

TRUE			true
FALSE			false
WHITESPACE		[ \t\r]
LF				[\n]

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
<SINGLE_QUOTED_CHAR>\'			{ if(strlen(literal) == 1) { yylval.Char = literal[0]; BEGIN(INITIAL); return CHAR_VAL;}}

\"									{ BEGIN(DOUBLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
<DOUBLE_QUOTED_STRING>[^%\"]			{ strcat(literal, yytext);}
<DOUBLE_QUOTED_STRING>\"			{ BEGIN(INITIAL); yylval.String=(char *)malloc(strlen(literal)+1); strcpy(yylval.String, literal); return STRING_VAL;}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%\/[0-9]{1,3}\/	{ append_special_char_by_code(literal, yytext);}
<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%.			{ append_special_char_digraph(literal, yytext);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING><<EOF>>	{ printf("Unterminated string or char literal at line %d\n", yylineno);  BEGIN(INITIAL);}

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment at line %d\n",yylineno); BEGIN(INITIAL);}

":="					{ return ASSIGN;}
"="						{ return EQUALS;}
"/="					{ return NOT_EQUALS;}
"<" 					{ return LESS;}
"<=" 					{ return LESS_OR_EQUAL;}
">" 					{ return GREATER;}
">=" 					{ return GREATER_OR_EQUAL;}
"and" 					{ return AND;}
"xor" 					{ return XOR;}
"or" 					{ return OR;}
"not" 					{ return NOT;}
and{WHITESPACE}+then 	{ return AND_THEN;}
or{WHITESPACE}+else 	{ return OR_ELSE;}
"implies" 				{ return IMPLIES;}

"+" 					{ return yytext[0];}
"-" 					{ return yytext[0];}
"*" 					{ return yytext[0];}
"/"						{ return yytext[0];}
"^" 					{ return yytext[0];}
";" 					{ return yytext[0];}

"(" 					{ return yytext[0];}
")" 					{ return yytext[0];}
"{" 					{ return yytext[0];}
"}" 					{ return yytext[0];}
"[" 					{ return yytext[0];}
"]" 					{ return yytext[0];}
":" 					{ return yytext[0];}
"." 					{ return yytext[0];}
"," 					{ return yytext[0];}

"if" 					{ return IF;}
"local" 				{ return LOCAL;}
"do" 					{ return DO;}
"end" 					{ return END;}
"elseif" 				{ return ELSEIF;}
"then" 					{ return THEN;}
"else" 					{ return ELSE;}
"class" 				{ return CLASS;}
"from" 					{ return FROM;}
"until" 				{ return UNTIL;}
"loop" 					{ return LOOP;}
"create" 				{ return CREATE;}
"feature" 				{ return FEATURE;}
"Result" 				{ return RESULT;}
"Current" 				{ return CURRENT;}
"Precursor" 			{ return PRECURSOR;}
"inherit" 				{ return INHERIT;}
"redefine" 				{ return REDEFINE;}

"ARRAY" 				{ return ARRAY;}
"INTEGER" 				{ return INTEGER;}
"REAL" 					{ return REAL;}
"CHARACTER" 			{ return CHARACTER;}
"STRING" 				{ return STRING;}
"BOOLEAN" 				{ return BOOLEAN;}

{TRUE}					{ yylval.Bool = true; return BOOL_VAL;}
{FALSE}					{ yylval.Bool = false; return BOOL_VAL;}
{ID}					{ yylval.String=(char *)malloc(strlen(yytext)+1); strcpy(yylval.String, yytext); return ID;}

{EXPONENT}				{ yylval.Real = parse_real(yytext); return REAL_VAL;}
{INT_10}				{ yylval.Int = parse_int(yytext, 'd'); return INT_VAL;}
{INT_16}				{ yylval.Int = parse_int(yytext, 'x'); return INT_VAL;}
{INT_8}					{ yylval.Int = parse_int(yytext, 'c'); return INT_VAL;}
{INT_2}					{ yylval.Int = parse_int(yytext, 'b'); return INT_VAL;}

{REAL}[^.]				{ yylval.Real = parse_real(yytext); return REAL_VAL;}

{LF}					{ if (global_LF_enabled) return LF;}
{WHITESPACE}+			{ /* skip  {WHITESPACE} */ }

<*>.					{ printf("Unexpected char \'%c\' encountered at line %d\n", yytext, yylineno);  BEGIN(INITIAL);}
%%