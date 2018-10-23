%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <conio.h>
	#include <locale.h> 

	#include "lexHelpers.h"
	#include "eiffel_bison.tab.h"

%}

%option noyywrap
%option never-interactive
%option yylineno

ID				[a-z][_a-z0-9]*

TRUE			true
FALSE			false
VOID 			void
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
<SINGLE_QUOTED_CHAR>\'			{ if(strlen(literal) == 1) {
										printf("Found single quoted literal \'%c\'. From line %d to line %d\n", literal[0], startLine, yylineno);
										yylval.Char = literal[0]; 
										return CHAR_VAL;
								  } else {
										printf("Invalid single quoted literal \'%s\' at line %d\n", literal, yylineno);
								  }
								  BEGIN(INITIAL);
								}

\"									{ BEGIN(DOUBLE_QUOTED_STRING); literal[0] = '\0'; startLine = yylineno; }
<DOUBLE_QUOTED_STRING>[^%\"]			{ strcat(literal, yytext);}
<DOUBLE_QUOTED_STRING>\"			{ printf("Found double quoted literal \"%s\". From line %d to line %d\n", literal, startLine, yylineno)
									  strcat(yylval.String, literal);
									  return STRING_VAL;
									  BEGIN(INITIAL);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%\/[0-9]{1,3}\/	{ append_special_char_by_code(literal, yytext);}
<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING>%.			{ append_special_char_digraph(literal, yytext);}

<SINGLE_QUOTED_CHAR,DOUBLE_QUOTED_STRING><<EOF>>	{ printf("Unterminated string or char literal at line %d\n", yylineno);  BEGIN(INITIAL);}

"--"								{ BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>[^\n]			/* skip */
<SINGLE_LINE_COMMENT>\n				{ printf("Found a comment\n"); BEGIN(INITIAL);}

":="					{ return ASSIGN; printf("Found operator \"%s\" in line %d\n", "ASSIGN", yylineno); }
"="						{ return EQUALS; printf("Found operator \"%s\" in line %d\n", "EQUALS", yylineno); }
"/="					{ return NOT_EQUALS; printf("Found operator \"%s\" in line %d\n", "NOT_EQUALS", yylineno); }
"<" 					{ return LESS; printf("Found operator \"%s\" in line %d\n", "LESS", yylineno); }
"<=" 					{ return LESS_OR_EQUAL; printf("Found operator \"%s\" in line %d\n", "LESS_OR_EQUAL", yylineno); }
">" 					{ return GREATER; printf("Found operator \"%s\" in line %d\n", "GREATER", yylineno); }
">=" 					{ return GREATER_OR_EQUAL; printf("Found operator \"%s\" in line %d\n", "GREATER_OR_EQUAL", yylineno); }
"and" 					{ return AND; printf("Found operator \"%s\" in line %d\n", "AND", yylineno); }
"xor" 					{ return XOR; printf("Found operator \"%s\" in line %d\n", "XOR", yylineno); }
"or" 					{ return OR; printf("Found operator \"%s\" in line %d\n", "OR", yylineno); }
"not" 					{ return NOT; printf("Found operator \"%s\" in line %d\n", "NOT", yylineno); }
and{WHITESPACE}+then 	{ return AND_THEN; printf("Found operator \"%s\" in line %d\n", "AND_THEN", yylineno); }
or{WHITESPACE}+else 	{ return OR_ELSE; printf("Found operator \"%s\" in line %d\n", "OR_ELSE", yylineno); }
"implies" 				{ return IMPLIES; printf("Found operator \"%s\" in line %d\n", "IMPLIES", yylineno); }

"+" 					{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"-" 					{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"*" 					{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"/"						{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
"^" 					{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }
";" 					{ return yytext; printf("Found operator \"%s\" in line %d\n", yytext, yylineno); }

"(" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
")" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"{" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"}" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"[" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"]" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
":" 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"." 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }
"," 					{ return yytext; printf("Found symbol \"%s\" in line %d\n", yytext, yylineno); }

"if" 					{ return IF; printf("Found keyword \"%s\" in line %d\n", "IF", yylineno); }
"local" 				{ return LOCAL; printf("Found keyword \"%s\" in line %d\n", "LOCAL", yylineno); }
"do" 					{ return DO; printf("Found keyword \"%s\" in line %d\n", "DO", yylineno); }
"end" 					{ return END; printf("Found keyword \"%s\" in line %d\n", "END", yylineno); }
"elseif" 				{ return ELSEIF; printf("Found keyword \"%s\" in line %d\n", "ELSEIF", yylineno); }
"then" 					{ return THEN; printf("Found keyword \"%s\" in line %d\n", "THEN", yylineno); }
"else" 					{ return ELSE; printf("Found keyword \"%s\" in line %d\n", "ELSE", yylineno); }
"class" 				{ return CLASS; printf("Found keyword \"%s\" in line %d\n", "CLASS", yylineno); }
"from" 					{ return FROM; printf("Found keyword \"%s\" in line %d\n", "FROM", yylineno); }
"until" 				{ return UNTIL; printf("Found keyword \"%s\" in line %d\n", "UNTIL", yylineno); }
"loop" 					{ return LOOP; printf("Found keyword \"%s\" in line %d\n", "LOOP", yylineno); }
"create" 				{ return CREATE; printf("Found keyword \"%s\" in line %d\n", "CREATE", yylineno); }
"feature" 				{ return FEATURE; printf("Found keyword \"%s\" in line %d\n", "FEATURE", yylineno); }
"Result" 				{ return RESULT; printf("Found keyword \"%s\" in line %d\n", "RESULT", yylineno); }
"Current" 				{ return CURRENT; printf("Found keyword \"%s\" in line %d\n", "CURRENT", yylineno); }
"Precursor" 			{ return PRECURSOR; printf("Found keyword \"%s\" in line %d\n", "PRECURSOR", yylineno); }

"ARRAY" 				{ return ARRAY; printf("Found keyword \"%s\" in line %d\n", "ARRAY", yylineno); }
"INTEGER" 				{ return INTEGER; printf("Found keyword \"%s\" in line %d\n", "INTEGER", yylineno); }
"REAL" 					{ return REAL; printf("Found keyword \"%s\" in line %d\n", "REAL", yylineno); }
"CHARACTER" 			{ return CHARACTER; printf("Found keyword \"%s\" in line %d\n", "CHARACTER", yylineno); }
"STRING" 				{ return STRING; printf("Found keyword \"%s\" in line %d\n", "STRING", yylineno); }
"BOOLEAN" 				{ return BOOLEAN; printf("Found keyword \"%s\" in line %d\n", "BOOLEAN", yylineno); }

{TRUE}					{ yylval.Bool = true; return BOOL_VAL; printf("Found boolean value \"%d\" in line %d\n", true, yylineno); }
{FALSE}					{ yylval.Bool = false; return BOOL_VAL; printf("Found boolean value \"%d\" in line %d\n", false, yylineno); }
{VOID}					{ printf("Found null-value \"%s\" in line %d\n", "<void>", yylineno); }
{ID}					{ strcat(yylval.String, yytext); return ID; printf("Found identifier \"%s\" in line %d\n", yytext, yylineno); }

{EXPONENT}				{ yylval.Real = parse_real(yytext); return REAL_VAL; printf("Found exponent value \"%e\" in line %d\n", yy_parse_real(yytext), yylineno); }
{INT_10}				{ yylval.Int = parse_int(yytext); return INT_VAL; printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext), yylineno); /*{NATURAL}	{ printf("Found unsigned int value \"%s\" in line %d\n", yytext, yylineno); }*/ }
{INT_16}				{ yylval.Int = parse_int(yytext, 'x'); return INT_VAL; printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'x'), yylineno);}
{INT_8}					{ yylval.Int = parse_int(yytext, 'c'); return INT_VAL; printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'c'), yylineno);}
{INT_2}					{ yylval.Int = parse_int(yytext, 'b'); return INT_VAL; printf("Found int value \"%d\" in line %d\n", yy_parse_int(yytext, 'b'), yylineno);}

{REAL}[^.]				{ yylval.Real = parse_real(yytext); return REAL_VAL; printf("Found real value \"%f\" in line %d\n", yy_parse_real(yytext), yylineno);}

{LF}					{ return LF; printf("Found line feed in line %d\n", yylineno); }
{WHITESPACE}+			{ /* skip  {WHITESPACE} */ }

<*>.					{ printf("Unexpected char \'%c\' encountered at line %d\n", yytext, yylineno);  BEGIN(INITIAL);}
%%