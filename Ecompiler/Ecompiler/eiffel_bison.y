%{
	/*Пролог*/
	#include "tree_structs.h"
	
	/* более подробные собщения об ошибках */
#define YYERROR_VERBOSE 1
	
	void yyerror (char const *s)
	{
	  fprintf (stderr, "%s\n", s);
	}	
	/*
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

%union {
int Int;
double Real;
char Char;
char *String;
bool Bool;
/*struct Program* prog;
struct Class* cls;
struct Class_List* cls_list;
struct Expression* exp;
struct EXAMPLE* ex;*/
}
/* более подробные собщения об ошибках */
%define parse.error verbose

%token <Int> INT_VAL
%token REAL_VAL
%token CHAR_VAL
%token STRING_VAL
%token BOOL_VAL
%token ID
%token ASSIGN IF LOCAL DO END ELSEIF THEN ELSE CLASS FROM UNTIL LOOP CREATE FEATURE RESULT CURRENT PRECURSOR
%token ARRAY INTEGER REAL CHARACTER STRING BOOLEAN


%left ';' LF
%left '[' ']'
%left IMPLIES
%left OR OR_ELSE XOR
%left AND AND_THEN
%left EQUALS NOT_EQUALS LESS GREATER LESS_OR_EQUAL GREATER_OR_EQUAL
%left CHAR_INTERVAL INT_INTERVAL
%left '+' '-'
%left '*' '/'
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
| '{' ID '}'
| '{' id_list_2_or_more '}'
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

subscript: access '[' expr ']'
;

qualification: ID '.'
| RESULT '.'
| CURRENT '.'
| qualification '(' expr_list_opt ')' '.'
;

qualification_list: qualification
| qualification_list qualification
;

lf: LF
| lf LF
;

stmt_sep: ';'
| lf
;

stmt: assign_stmt 
| access stmt_sep
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
| ARRAY '[' type ']'
| INTEGER
| REAL
| CHARACTER
| STRING
| BOOLEAN
;

type_mark: ':' type
;

expr: INT_VAL
| REAL_VAL
| CHAR_VAL
| STRING_VAL
| BOOL_VAL
| access
| subscript
| '(' expr ')'
| NOT expr
| '+' expr %prec UPLUS
| '-' expr %prec UMINUS
| expr '^' expr
| expr '*' expr
| expr '/' expr
| expr '+' expr
| expr '-' expr
| expr EQUALS expr
| expr NOT_EQUALS expr
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

assign_stmt: ID ASSIGN expr stmt_sep
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

param: ID type_mark
;

return_value: type_mark
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

vars_declaration: ID type_mark
| id_list_2_or_more type_mark
;

id_list_2_or_more: ID ',' ID
| id_list_2_or_more ',' ID
;


error_token: INT_INTERVAL	{ yyerror("Forbidden token: INT_INTERVAL"); YYERROR;}
		   | CHAR_INTERVAL	{ yyerror("Forbidden token: CHAR_INTERVAL");YYERROR;}
		   ;

%%
{/*Секция пользовательского кода*/}
