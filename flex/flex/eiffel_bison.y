%{

	//Пролог
	#include "tree_structs.h"
%}

%union {
int Int;
char Char;
char *String;
bool Bool;
struct Program* prog;
struct Class* cls;
struct Class_List* cls_list;
struct Expression* exp;
struct EXAMPLE* ex;
}

%start program
%type class_list
%type class
%type stmt_list
%type stmt
%type expr
%type assign_expr
%type if_stmt

%token <Int> INT
%token <Int> REAL
%token <Char> CHAR
%token <String> STRING
%token <Bool> TRUE
%token <Bool> FALSE
%token <String> ID
%token <String> IF
%token <String> END
%token <String> ELSEIF
%token <String> THEN
%token <String> ELSE

%right ASSIGN
%left ';'
%left '[' ']'
%left IMPLIES
%left OR OR_ELSE XOR
%left AND AND_THEN
%left EQUALS NOT_EQUALS BIT_EQUALS BIT_NOT_EQUALS LESS GREATER LESS_OR_EQUAL GREATER_OR_EQUAL
%left CHAR_INTERVAL INT_INTERVAL
%left '+' '-'
%left '*' '/' DIV MOD
%left '^'
%left OLD NOT UPLUS UMINUS
%left '.'
%nonassoc ')'

%%

program : class_list
;

class_list: class
| class_list class
;

stmt_list: stmt
| stmt_list stmt
;

stmt: ';' {/*?*/}
| expr ';'
| expr
| assign_expr ';'
| assign_expr
| if_stmt
;

expr: INT 
| REAL
| CHAR
| STRING
| ID
| FALSE
| TRUE
| '(' expr ')'
| OLD expr
| NOT expr
| '+' expr %prec UPLUS
| '-' expr %prec UMINUS
| expr '^' expr
| expr '*' expr
| expr '/' expr
| expr DIV expr
| expr MOD expr
| expr '+' expr
| expr '-' expr
| expr '+' expr
| expr EQUALS expr
| expr NOT_EQUALS expr
| expr BIT_EQUALS expr
| expr BIT_NOT_EQUALS expr
| expr LESS expr
| expr GREATER expr
| expr LESS_OR_EQUAL expr
| expr GREATER_OR_EQUAL expr
| expr AND expr
| expr AND_THEN expr
| expr OR expr
| expr OR_ELSE expr
| expr XOR expr
| expr IMPLIES expr
| expr '[' expr ']'
;

assign_expr: ID ASSIGN expr
;


if_stmt: IF then_part_list END
| IF then_part_list else_part END
;

then_part_list: then_part
| then_part_list ELSEIF then_part 
;

then_part: '(' expr ')' THEN stmt_list
;

else_part: ELSE stmt_list
;


routine: ID params_opt return_value local_opt DO stmt_list END
;

params_opt: '(' param_list ')'
| /*empty*/
;

param_list: param
| param_list ';' param
;

param: ID ':' ID
;

return_value: ':' ID
| /*empty*/
;

local_opt: LOCAL declaration_list
| /*empty*/
;

declaration_list: declaration
| declaration_list declaration
;

declaration: id_list ':' ID
;

id_list: ID
| id_list ',' ID
;


%%
{/*Секция пользовательского кода*/}