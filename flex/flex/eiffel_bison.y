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
%type <prog> assign_stmt
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
%token CLASS, FROM, UNTIL, LOOP, CREATE

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

class: CLASS ID class_body END
;

class_body: creation_list feature_list
;

creation_list: CREATE ID
| creation_list ',' ID
;

feature_list: feature
| feature_list feature
;

feature: attribute
| routine
;

attribute: declaration
;

stmt_list: stmt 
| stmt_list stmt
;

stmt_list_opt: /*empty*/
| stmt_list 
;

stmt: assign_stmt ';'
| assign_stmt
| if_stmt
| from_loop
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

assign_stmt: ID ASSIGN expr
;

assign_stmt_list: assign_stmt
| assign_stmt_list assign_stmt
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

from_loop: FROM stmt_list_opt UNTIL expr LOOP stmt_list END
;

routine: ID '(' param_list ')' return_value local_opt DO stmt_list END
| ID return_value local_opt DO stmt_list END
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