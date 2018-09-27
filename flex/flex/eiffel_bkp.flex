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
	// TRUE 			[tT][rR][uU][eE]
	// FALSE 			[fF][Aa][lL][sS][eE]

BOOLEAN			true|false
VOID 			void
WHITESPACE		[ \t\n\r]+

INTENGER		[1-9][0-9]*|0

NUM          	[0-9]+
REAL          	([0-9]*[\.]{NUM})|({NUM}[\.][0-9]*)

KEYWORD (agent|alias|all|as|assign|attribute|check|class|convert|create|Current|debug|deferred|do|else|elseif|end|ensure|expanded|export|external|feature|from|frozen|if|implies|inherit|inspect|invariant|like|local|loop|not|note|obsolete|old|once|only|Precursor|redefine|rename|require|rescue|Result|retry|select|separate|then|TUPLE|undefine|until|variant|when)

%x SPECIAL_CHAR
%x SINGLE_QUOTED_CHAR
%x DOUBLE_QUOTED_STRING
%x SINGLE_LINE_COMMENT

%%

%{
	int startLine = 0;
	char literal[1000];
%}

\'									{ BEGIN(SINGLE_QUOTED_CHAR); literal[0] = '\0'; startLine = yylineno; }
<SINGLE_QUOTED_CHAR>\\n			{ strcat(literal, yytext);}
<SINGLE_QUOTED_CHAR>\\\\			{ strcat(literal, "\\");}
<SINGLE_QUOTED_CHAR>\\\'			{ strcat(literal, "\'");}
<SINGLE_QUOTED_CHAR>[^\']		{ strcat(literal, yytext);}
<SINGLE_QUOTED_CHAR>\'			{ printf("Found single quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

\"									{ BEGIN(DOUBLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
\0 // <DOUBLE_QUOTED_STRING>\\n			{ strcat(literal, yytext);}
\0 // <DOUBLE_QUOTED_STRING>\\\\			{ strcat(literal, "\\");}
\0 //<DOUBLE_QUOTED_STRING>\\\'			{ strcat(literal, "\'");}
<DOUBLE_QUOTED_STRING>[^%\"]			{ strcat(literal, yytext);}
<DOUBLE_QUOTED_STRING>\"			{ printf("Found double quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno); BEGIN(INITIAL);}

\0 //<*>%								{ BEGIN(SPECIAL_CHAR); }
\0 //<*>%/								{ BEGIN(SPECIAL_CHAR); }

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment\n"); BEGIN(INITIAL);}


{KEYWORD}				{ printf("Found keyword \"%s\" in line %d\n", yytext, yylineno); }

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
\' 						{ printf("Found SINGLE-QUOTE symbol \"%s\" in line %d\n", yytext, yylineno); }
\" 						{ printf("Found DOUBLE-QUOTE symbol \"%s\" in line %d\n", yytext, yylineno); }
"$" 					{ printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }

{BOOLEAN}				{ printf("Found boolean value \"%s\" in line %d\n", yytext, yylineno); }
{VOID}					{ printf("Found null-value \"%s\" in line %d\n", yytext, yylineno); }
{INTENGER}				{ printf("Found int value \"%s\" in line %d\n", yytext, yylineno); }
{REAL}					{ printf("Found real value \"%s\" in line %d\n", yytext, yylineno); }
{ID}					{ printf("Found identifier \"%s\" in line %d\n", yytext, yylineno); }

{WHITESPACE}				{ /* skip  {WHITESPACE} */ }


%%