%{
	/*Пролог*/
	#include "tree_structs.h"
	/*
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
%type <prog> class_list
%type <prog> class
%type <prog> stmt_list
%type <prog> stmt
%type <prog> expr
%type <prog> assign_expr
%type <prog> if_stmt
	
	*/
%}

%token INT
%token REAL
%token CHAR
%token STRING
%token BOOL
%token ID
%token ASSIGN
%token IF
%token LOCAL
%token DO
%token END
%token ELSEIF
%token THEN
%token ELSE

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
| error_token
;

class_list: class
| class_list class
;

class: stmt_list END
;

stmt_list: stmt 
| stmt_list stmt
;

stmt: assign_expr ';'
| assign_expr
| if_stmt
;

expr: INT 
| REAL
| CHAR
| STRING
| ID
| BOOL
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

error_token: INT_INTERVAL	{ printf("Forbidden token: %s", $1); return 1;}
		   | CHAR_INTERVAL	{ printf("Forbidden token: %s", $1); return 1;}
		   ;

%%
{/*Секция пользовательского кода*/}