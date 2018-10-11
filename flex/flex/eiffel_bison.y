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
%token ASSIGN IF LOCAL DO END ELSEIF THEN ELSE CLASS FROM UNTIL LOOP CREATE FEATURE RESULT CURRENT PRECURSOR


%left ';'
%left IMPLIES
%left OR OR_ELSE XOR
%left AND AND_THEN
%left EQUALS NOT_EQUALS BIT_EQUALS BIT_NOT_EQUALS LESS GREATER LESS_OR_EQUAL GREATER_OR_EQUAL
%left CHAR_INTERVAL INT_INTERVAL
%left '+' '-'
%left '*' '/' DIV MOD
%left '^'
%left NOT UPLUS UMINUS
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

class_body: creation_list feature_clauses
;

creation_list: CREATE ID
| creation_list ',' ID
;

feature_clauses:  FEATURE clients_opt feature_declaration_list
| feature_clauses FEATURE clients_opt feature_declaration_list
;

clients_opt: /*empty*/
| '{' id_list '}'
;

feature_declaration_list:  feature_declaration
| feature_declaration_list feature_declaration
;

feature_declaration: attribute
| routine
;

attribute: vars_declaration
;

access: 			 ID
| qualification_list ID 
| 					 ID '(' expr_list_opt ')'
| qualification_list ID '(' expr_list_opt ')'
;

qualification: ID '.'
| RESULT '.'
| CURRENT '.'
| qualification '(' expr_list_opt ')' '.'
;

qualification_list: qualification
| qualification_list qualification
;


stmt: stmt ';'
| assign_stmt
| access
| if_stmt
| from_loop
;

stmt_list: stmt 
| stmt_list stmt
;

stmt_list_opt: /*empty*/
| stmt_list 
;

type: ID
;

expr: INT 
| REAL
| CHAR
| STRING
| access { /*
	| ID	*/ }
| BOOL
| '(' expr ')'
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
| RESULT
| CURRENT
| PRECURSOR   {/**/}
| CREATE '{' type '}' access
;

expr_list: expr
| expr_list ',' expr
;

expr_list_opt: expr_list
| /*empty*/
;

assign_stmt: ID ASSIGN expr
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


routine: ID param_list_0_or_more return_value_opt local_vars_opt routine_body
| ID return_value local_vars routine_body
| ID  return_value  routine_body
| ID  local_vars routine_body
| ID   routine_body
;

routine_body: DO stmt_list_opt END
;

param_list_0_or_more: '(' param_list ')'
| '(' ')'
;

param_list: param
| param_list ';' param
;

param: ID ':' type
;

return_value: ':' type
;

return_value_opt: return_value
| /*empty*/
;

local_vars: LOCAL declaration_list
;

local_vars_opt: local_vars
| /*empty*/
;

declaration_list: vars_declaration
| declaration_list vars_declaration
;

vars_declaration: ID ':' type
| id_list ':' type
;

id_list: ID ',' ID
| id_list ',' ID
;


error_token: INT_INTERVAL	{ printf("Forbidden token: %s", $1); return 1;}
		   | CHAR_INTERVAL	{ printf("Forbidden token: %s", $1); return 1;}
		   ;

%%
{/*Секция пользовательского кода*/}