%{
/*Пролог*/
#include "tree_structs.h"
	
/* более подробные собщения об ошибках */
#define YYERROR_VERBOSE 1
	
// Флаг для управления контекстом Flex`а
int global_LF_enabled = false
%}

%union {
int Int;
double Real;
char Char;
char* String;
boolean Bool;

/*структуры для узлов*/
struct NId* id_struct;
struct NIdList* id_list_struct;
struct NExpr* expr_struct;
struct NExprList* expr_list_struct;
struct NAccess* access_struct;
struct NRef* ref_struct;
struct NRefChain* ref_chain_struct;
struct NStmt* stmt_struct;
struct NStmtList* stmt_list_struct;
struct NType* type_struct;
struct NAssignStmt* assign_stmt_struct;
struct NIfStmt* if_stmt_struct;
struct NThenPart* then_part_struct;
struct NThenPartList* then_part_list_struct;
struct NElsePart* else_part_struct;
struct NLoopStmt* loop_stmt_struct;
struct NClass* class_struct;
struct NClassList* class_list_struct;
struct NFeature* feature_struct;
struct NFeatureList* feature_list_struct;
struct NNameAndType* name_and_type_struct;
struct NNameAndTypeList* name_and_type_list_struct;

// struct * _struct;
}

/*нетерминалы*/
%start program
%type <class_list_struct> class_list
%type <class_struct> class
%type <Int> class_body
%type <id_list_struct> creation_list
%type <NIdList> feature_clauses
%type <NIdList> clients_opt
%type <feature_list_struct> feature_declaration_list
%type <feature_struct> feature_declaration
%type <access_struct> access
%type <ref_struct> ref
%type <ref_chain_struct> ref_chain
%type <Int> stmt_sep
%type <stmt_struct> stmt
%type <stmt_list_struct> stmt_list
%type <stmt_list_struct> stmt_list_opt
%type <type_struct> type
%type <type_struct> type_mark
%type <expr_struct> expr
%type <expr_list_struct> expr_list
%type <expr_list_struct> expr_list_opt
%type <assign_stmt_struct> assign_stmt
%type <if_stmt_struct> if_stmt
%type <then_part_list_struct> then_part_list
%type <then_part_struct> then_part
%type <else_part_struct> else_part
%type <loop_stmt_struct> from_loop
%type <feature_struct> routine
%type <stmt_list_struct> routine_body
%type <name_and_type_list_struct> param_list_0_or_more
%type <name_and_type_list_struct> param_list
%type <name_and_type_struct> param
%type <type_struct> return_value
%type <type_struct> return_value_opt
%type <name_and_type_list_struct> local_vars
%type <name_and_type_list_struct> local_vars_opt
%type <name_and_type_list_struct> declaration_list
%type <name_and_type_list_struct> vars_declaration
%type <id_list_struct> id_list_2_or_more
/* %type <> error_token */


/* более подробные собщения об ошибках */
%define parse.error verbose

%token <Int> INT_VAL
%token <Real> REAL_VAL
%token <Char> CHAR_VAL
%token <String> STRING_VAL
%token <Bool> BOOL_VAL
%token <String> ID
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
| feature_clauses
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

feature_declaration: vars_declaration /*attribute*/
| routine
;

access: ID	{$$=createAccess(IdA, $1, 0);}
| 		RESULT	{$$=createAccess(ResultA, 0, 0);}
| 		CURRENT	{$$=createAccess(CurrentA, 0, 0);}
|		PRECURSOR	{$$=createAccess(PrecursorA, 0, 0);}
| 		ID '(' expr_list_opt ')'	{$$=createAccess(IdA, $1, $3);}
;

ref: access	{$$=createRef($1,0);}
| access '[' expr ']' {$$=createRef($1,$3);}
;

ref_chain: ref	{$$=createRefChain($1);}
| ref_chain '.' ref {$$=addToRefChain($1, $3);}
;

/* actions only */
_LF_ON_:  { global_LF_enabled = true; }
;
_LF_OFF_: { global_LF_enabled = false;}
;

stmt_sep: ';'
| LF
| stmt_sep LF
;

stmt: _LF_ON_ CREATE ref_chain stmt_sep _LF_OFF_
| _LF_ON_ assign_stmt _LF_OFF_
| _LF_ON_ ref_chain stmt_sep _LF_OFF_
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

expr: INT_VAL	{$$=createIntConstExpr($1);}
| REAL_VAL		{$$=createRealConstExpr($1);}
| CHAR_VAL		{$$=createCharConstExpr($1);}
| STRING_VAL	{$$=createStringConstExpr($1);}
| BOOL_VAL		{$$=createBoolConstExpr($1);}
| ref_chain		{$$=createRefExpr($1); }
| '(' expr ')'	{$$=$2;}
| NOT expr		{$$=createExpr(NotE,$2,0);}
| '+' expr %prec UPLUS	{$$=createExpr(UPlusE,$2,0);}
| '-' expr %prec UMINUS	{$$=createExpr(UMinusE,$2,0);}
| expr '^' expr	{$$=createExpr(PowerE,$1,$3);}
| expr '*' expr	{$$=createExpr(MulE,$1,$3);}	
| expr '/' expr	{$$=createExpr(DivE,$1,$3);}
| expr '+' expr	{$$=createExpr(PlusE,$1,$3);}
| expr '-' expr	{$$=createExpr(MinusE,$1,$3);}
| expr EQUALS expr	{$$=createExpr(EqualsE,$1,$3);}
| expr NOT_EQUALS expr	{$$=createExpr(NotEqualE,$1,$3);}
| expr LESS expr	{$$=createExpr(LessE,$1,$3);}
| expr GREATER expr	{$$=createExpr(GreaterE,$1,$3);}
| expr LESS_OR_EQUAL expr	{$$=createExpr(LessOrEqualE,$1,$3);}
| expr GREATER_OR_EQUAL expr	{$$=createExpr(GreaterOrEqualE,$1,$3);}
| expr AND expr	{$$=createExpr(AndE,$1,$3);}
| expr AND_THEN expr	{$$=createExpr(AndThenE,$1,$3);}
| expr OR expr	{$$=createExpr(OrE,$1,$3);}
| expr OR_ELSE expr	{$$=createExpr(OrElseE,$1,$3);}
| expr XOR expr	{$$=createExpr(XORE,$1,$3);}
| expr IMPLIES expr	{$$=createExpr(ImpliesE,$1,$3);}
;

expr_list: expr	{$$=createExprList($1);}
| expr_list ',' expr {$$=addToExprList($1, $3);}
;

expr_list_opt: expr_list	{$$=createExprList($1);}
| /*empty*/	{$$=createExprList(0);}
;

assign_stmt: ref_chain ASSIGN expr stmt_sep {$$=createAssignStmt($1, $3);}
;


if_stmt: IF then_part_list END	{$$=createIfStmt($2, 0);}
| IF then_part_list else_part END 	{$$=createIfStmt($2, $3);}
;

then_part_list: then_part	{$$=createThenPartList($1);}
| then_part_list ELSEIF then_part	{$$=addToThenPartList($1, $3);} 
;

then_part: '(' expr ')' THEN stmt_list	{$$=createThenPart($2, $5);}
;

else_part: ELSE stmt_list	{$$=createElsePart($2);}
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

/*
error_token: INT_INTERVAL	{ yyerror("Forbidden token: INT_INTERVAL"); YYERROR;}
		   | CHAR_INTERVAL	{ yyerror("Forbidden token: CHAR_INTERVAL");YYERROR;}
		   ;
*/
%%
/*Секция пользовательского кода*/
#include "bisonFunctions.c"

void yyerror (char const *s)
{
  // fprintf (stderr, "%s\n", s);
}	

// переменные, глобальные для анализатора
struct NClass* currentNClass = NULL;
struct NIdList* currentFeatureClients;
struct NType* currentType;

