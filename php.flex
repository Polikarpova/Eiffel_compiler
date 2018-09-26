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

ID				[a-zA-Z_\x7f-\xff][a-zA-Z0-9_\x7f-\xff]*
TRUE 			[tT][rR][uU][eE]
FALSE 			[fF][Aa][lL][sS][eE]
NULL 			[Nn][uU][lL]{2}

INT_10 			[1-9][0-9]*|0
INT_16 			0[xX][0-9a-fA-F]+
INT_8 			[0-7]+
INT_2 			0b[01]+

NUM          	[0-9]+
FLOAT          	([0-9]*[\.]{NUM})|({NUM}[\.][0-9]*)
EXPONENT	 	(({NUM}|{FLOAT})[eE][+-]?{NUM})	

%x PHP
%x ONE_LINE_COMMENT
%x MULTILINE_COMMENT
%x HTML_COMMENT
%x SINGLE_QUOTED_STRING
%x DOUBLE_QUOTED_STRING
%x HEREDOC
%x NOWDOC

%%

%{
	int s = 0;
	char buf[100000];
%}

[^(\<\?(php)?)]					;

"<!--"							{ BEGIN(HTML_COMMENT); s = yylineno; }
<HTML_COMMENT>[^\-]+			{ ; }
<HTML_COMMENT>"-"				{ ; }
<HTML_COMMENT>\-{2}\>			{ BEGIN(INITIAL); printf("Founded HTML-comment from line %d to line %d\n", s, yylineno); }

<PHP>("//"|"#").*       		{ printf("Founded single line comment in line %d\n", yylineno); }

<PHP>"/*"						{ BEGIN(MULTILINE_COMMENT); s = yylineno; }
<MULTILINE_COMMENT>[^*]*		{ ; }
<MULTILINE_COMMENT>"*"+[^*/]* 	{ ; }
<MULTILINE_COMMENT>"*"+"/" 		{ BEGIN(PHP); printf("Founded multiline comment from line %d to line %d\n", s, yylineno); }

<PHP>\'							{ BEGIN(SINGLE_QUOTED_STRING); buf[0] = '\0'; s = yylineno; }
<SINGLE_QUOTED_STRING>\\n		{ strcat(buf, yytext); }
<SINGLE_QUOTED_STRING>\\\\		{ strcat(buf, yytext); }
<SINGLE_QUOTED_STRING>\\\'		{ strcat(buf, yytext); }
<SINGLE_QUOTED_STRING>[^\'\\n]	{ strcat(buf, yytext); }
<SINGLE_QUOTED_STRING>\'		{ BEGIN(PHP); printf("Founded single quoted literal \"%s\" from line %d to line %d\n", buf, s, yylineno); }

<HTML_COMMENT,MULTILINE_COMMENT><<EOF>>			{ BEGIN(INITIAL); printf("ERROR! Unexpected end of file!"); }

\<\?(php)?						{ BEGIN(PHP); printf("Founded start PHP-script in line %d\n", yylineno); }
<PHP>"<"(""|"/")[a-z]+\>		{ printf("ERROR! HTML inside PHP-script in line %d!", yylineno); }
<PHP>\?\>						{ BEGIN(INITIAL); printf("Founded end PHP-script in line %d\n", yylineno); }
<PHP><<EOF>>					{ BEGIN(INITIAL); printf("Founded end PHP-script in line %d\n", yylineno); }

<PHP>const						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>class						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>public						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>protected					{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>private					{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>new 						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>as							{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>and						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>or							{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>xor						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>break						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>continue					{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>do							{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>while						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>for						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>foreach					{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>echo						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>if							{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>elseif						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>else						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>function					{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>return						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }
<PHP>static						{ printf("Finded keyword \"%s\" in line %d\n", yytext, yylineno); }

<PHP>"++"						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"--"						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"!" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"*" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"**" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"/" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"%" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"+" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"." 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>":" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"," 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"-" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"<" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"<=" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>">" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>">=" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"==" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"!=" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"===" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"!==" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"&&" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"||" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"=" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"$" 						{ printf("Finded operator \"%s\" in line %d\n", yytext, yylineno); }

<PHP>";" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"(" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>")" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"{" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"}" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"[" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"]" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"::" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"->"						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }
<PHP>"=>" 						{ printf("Finded symbol \"%s\" in line %d\n", yytext, yylineno); }

<PHP>{ID}						{ printf("Finded identifier \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{TRUE}						{ printf("Finded boolean value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{FALSE}					{ printf("Finded boolean value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{NULL}						{ printf("Finded value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{INT_10}					{ printf("Finded int value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{INT_16}					{ printf("Finded int value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{INT_8}					{ printf("Finded int value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{INT_2}					{ printf("Finded int value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{FLOAT}					{ printf("Finded float value \"%s\" in line %d\n", yytext, yylineno); }
<PHP>{EXPONENT}					{ printf("Finded float value \"%s\" in line %d\n", yytext, yylineno); }

%%