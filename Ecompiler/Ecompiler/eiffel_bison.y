%{
/*ѕролог*/
#include "bisonFunctions.h"
	
/* более подробные собщени€ об ошибках */
#define YYERROR_VERBOSE 1

void yyerror (char const *s);	

// ‘лаг дл€ управлени€ контекстом Flex`а
int global_LF_enabled = false;

extern int yylex();

struct NClassList* root;

/* < Error handling > */
#define MAX_SYNTAX_ERRORS 20

char* syntax_errors[MAX_SYNTAX_ERRORS];
int syntax_errors_logged = 0;
void yyerror (const char *s); //  см. ниже: —екци€ пользовательского кода
/* </ Error handling > */


// запоминание текущего положени€
struct YYLTYPE global_loc;

/* eiffel_bison.tab.cpp: line 919
   YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do {                                                                \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
        global_loc = (Current);                                         \
    } while (0)

%}

// enable locations
%locations

// save .h file with `extern` defines
%defines

%union {
int Int;
double Real;
char Char;
char* String;
bool Bool;

/*структуры дл€ узлов*/
struct NId* id_struct;
struct NIdList* id_list_struct;
struct NExpr* expr_struct;
struct NExprList* expr_list_struct;
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
struct NInheritFromClass* inherit_class_struct;
struct NInheritFromClassList* inherit_class_list_struct;

}

/*нетерминалы*/
%start program
%type <class_list_struct> class_list
%type <class_struct> class
%type <inherit_class_list_struct> inheritance_opt
%type <inherit_class_list_struct> inheritance_list
%type <inherit_class_struct> inherit_from_class
%type <id_list_struct> clients_opt
%type <id_list_struct> redefine
%type <id_list_struct> redefine_opt
%type <id_list_struct> creation_list
%type <id_list_struct> creation_list_opt
%type <feature_list_struct> feature_clauses
%type <feature_list_struct> feature_clauses_opt
%type <feature_list_struct> feature_declaration_list
%type <feature_list_struct> attributes
%type <stmt_struct> stmt
%type <stmt_list_struct> stmt_list
%type <stmt_list_struct> stmt_list_opt
%type <type_struct> type
%type <type_struct> type_mark
%type <expr_struct> expr
%type <expr_list_struct> expr_list
%type <assign_stmt_struct> assign_stmt
%type <if_stmt_struct> if_stmt
%type <then_part_list_struct> then_part_list
%type <then_part_struct> then_part
%type <else_part_struct> else_part
%type <loop_stmt_struct> from_loop
%type <feature_struct> routine
%type <stmt_list_struct> routine_body
%type <name_and_type_list_struct> param_list_1_or_more
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


/* более подробные собщени€ об ошибках */
%define parse.error verbose

%token <Int> INT_VAL
%token <Real> REAL_VAL
%token <Char> CHAR_VAL
%token <String> STRING_VAL
%token <Bool> BOOL_VAL
%token <String> ID
%token ASSIGN IF LOCAL DO END ELSEIF THEN ELSE CLASS FROM UNTIL LOOP CREATE FEATURE PRECURSOR INHERIT REDEFINE
%token ARRAY INTEGER REAL CHARACTER STRING BOOLEAN


%left ';' LF
%left IMPLIES
%left OR OR_ELSE XOR
%left AND AND_THEN
%left EQUALS NOT_EQUALS LESS GREATER LESS_OR_EQUAL GREATER_OR_EQUAL
%left '+' '-'
%left '*' '/'
%left '^'
%left NOT UPLUS UMINUS
%nonassoc '(' ')'
%left '[' ']'
%left '.'
%nonassoc GROUP_BRACE

%%

program : class_list	{root = $1;}
| error	{root=0;}
;

class_list: class	{$$=createClassList($1);}
| class_list class	{$$=addToClassList($1,$2);}
| class_list error	{$$=$1;}
;

class: CLASS ID inheritance_opt creation_list_opt feature_clauses_opt END	{$$=createClass($2,$3,$4,$5);}
;

inheritance_opt: /*empty*/	{$$=0;}
| inheritance_list			{$$=$1;}
;
inheritance_list: INHERIT inherit_from_class {$$=createInheritFromClassList($2);}
| inheritance_list inherit_from_class		{$$=addInheritFromClassList($1,$2);}
| inheritance_list error					{$$=$1;}
;

inherit_from_class: ID /*rename_opt*/ /*undefine_opt*/ redefine_opt	{$$=createInheritFromClass($1,$2);}

redefine_opt: /*empty*/	{$$=0;}
| redefine				{$$=$1;}
;
redefine: REDEFINE ID END		{$$=createIdList(createId($2));}
| REDEFINE id_list_2_or_more END	{$$=$2;}
;

creation_list_opt: /*empty*/	{$$=0;}
| creation_list					{$$=$1;}
;
creation_list: CREATE ID	{$$=createIdList(createId($2));}
| creation_list ',' ID		{$$=addToIdList($1,createId($3));}
| creation_list ',' error	{$$=$1;}
;

feature_clauses_opt: /*empty*/	{$$=0;}
| feature_clauses				{$$=$1;}
;
feature_clauses:  FEATURE clients_opt feature_declaration_list  {$$=$3;}
| feature_clauses FEATURE clients_opt feature_declaration_list {$$=joinFeatureLists($1,$4);}
;

clients_opt: /*empty*/	{$$=registerClients(createIdList(createId("ANY")));}
| '{' ID '}'			{$$=registerClients(createIdList(createId($2)));}
| '{' id_list_2_or_more '}'	{$$=registerClients($2);}
;

feature_declaration_list: attributes  {$$=$1;}
| routine						{$$=createFeatureList($1);}
| feature_declaration_list attributes {$$=joinFeatureLists($1,$2);}
| feature_declaration_list routine {$$=addToFeatureList($1,$2);}
| feature_declaration_list error {$$=$1;}
;

attributes: vars_declaration {$$=createAttributesFrom($1);}
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

stmt: CREATE _LF_ON_ expr stmt_sep _LF_OFF_	{$$=createStmt(CreateSt,$3);}
| _LF_ON_ assign_stmt stmt_sep _LF_OFF_		{$$=createStmt(AssignSt,$2);}
| _LF_ON_ expr stmt_sep _LF_OFF_	{$$=createStmt(ExprSt,$2);}
| if_stmt			{$$=createStmt(IfSt,$1);}
| from_loop			{$$=createStmt(LoopSt,$1);}
;

stmt_list: error 	{$$=createStmtList(0);}
| stmt				{$$=createStmtList($1);}
| stmt_list stmt 	{$$=addToStmtList($1, $2);}
| stmt_list error 	{$$=$1;}
;

stmt_list_opt: /*empty*/	{$$=createStmtList(0);}
| stmt_list 		{$$=$1;}
;

type: ID		{$$=createType(ClassV,$1);}
| ARRAY '[' type ']' {$$=createType(ArrayV,0,$3);}
| INTEGER		{$$=createType(IntegerV);}
| REAL			{$$=createType(RealV);}
| CHARACTER		{$$=createType(CharacterV);}
| STRING		{$$=createType(StringV);}
| BOOLEAN		{$$=createType(BooleanV);}
;

type_mark: ':' type	{$$=$2;}
;

expr:
	/* Terminals */
  INT_VAL	{$$=createIntConstExpr($1);}
| REAL_VAL		{$$=createRealConstExpr($1);}
| CHAR_VAL		{$$=createCharConstExpr($1);}
| STRING_VAL	{$$=createStringConstExpr($1);}
| BOOL_VAL		{$$=createBoolConstExpr($1);}
	/* Grouping */
| '(' expr ')' %prec GROUP_BRACE	{$$=$2;}
	/* Unary */
| NOT expr		{$$=createExpr(NotE,$2,0);}
| '+' expr %prec UPLUS	{$$=createExpr(UPlusE,$2,0);}
| '-' expr %prec UMINUS	{$$=createExpr(UMinusE,$2,0);}
	/* Binary */
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
	/* Chains */
| expr '.' ID 	{$$=createRefnCallExpr($1,$3,0);}
| expr '.' ID '(' expr_list ')' {$$=createRefnCallExpr($1,$3,$5);}
| expr '[' expr ']' 	{$$=createExpr(SubscriptE,$1,$3);}
	/* IDs (locals, features) & calls */
| ID			{$$=createRefnCallExpr(0,$1,0);}
| ID '(' expr_list ')' {$$=createRefnCallExpr(0,$1,$3);}
| PRECURSOR		{$$=createPrecursorExpr(0,0);}
| PRECURSOR '{' ID '}'{$$=createPrecursorExpr($3,0);}
| PRECURSOR '(' expr_list ')'		{$$=createPrecursorExpr(0, $3);}
| PRECURSOR '{' ID '}' '(' expr_list ')' {$$=createPrecursorExpr($3, $6);}

;

expr_list: expr			{$$=createExprList($1);}
| expr_list ',' expr 	{$$=addToExprList($1, $3);}
| expr_list ',' error 	{$$=$1;}
;

assign_stmt: expr ASSIGN expr {$$=createAssignStmt($1, $3);}
;


if_stmt: IF then_part_list END	{$$=createIfStmt($2, 0);}
| IF then_part_list else_part END 	{$$=createIfStmt($2, $3);}
;

then_part_list: then_part	{$$=createThenPartList($1);}
| then_part_list ELSEIF then_part	{$$=addToThenPartList($1, $3);} 
;

then_part: expr THEN stmt_list_opt	{$$=createThenPart($1, $3);}
;

else_part: ELSE stmt_list_opt	{$$=createElsePart($2);}
;


from_loop: FROM stmt_list_opt UNTIL expr LOOP stmt_list_opt END	{$$=createFromLoop($2, $4, $6);}
;


routine: ID param_list_1_or_more return_value_opt local_vars_opt routine_body	{$$=createFeature($1,$2,$3,$4,$5);}
| ID return_value local_vars routine_body	{$$=createFeature($1,0,$2,$3,$4);}
| ID  return_value  routine_body	{$$=createFeature($1,0,$2,0,$3);}
| ID  local_vars routine_body	{$$=createFeature($1,0,createType(VoidV),$2,$3);}
| ID   routine_body				{$$=createFeature($1,0,createType(VoidV),0,$2);}
;

routine_body: DO stmt_list_opt END	{$$=$2;}
;

param_list_1_or_more: '(' param_list ')'	{$$=$2;}
;

param_list: param		{$$=createNameAndTypeList($1);}
| param_list ';' param	{$$=addToNameAndTypeList($1,$3);}
| param_list ';' error	{$$=$1;}
;

param: ID type_mark		{$$=createNameAndType($1,$2);}
;

return_value: type_mark	{$$=$1;}
;

return_value_opt: return_value	{$$=$1;}
| /*empty*/						{$$=0; }
;

local_vars: LOCAL declaration_list	{$$=$2;}
;

local_vars_opt: local_vars		{$$=$1;}
| /*empty*/						{$$=0; }
;

declaration_list: vars_declaration	{$$=$1;}
| declaration_list vars_declaration	{$$=joinNameAndTypeLists($1,$2);}
| declaration_list error			{$$=$1;}
;

vars_declaration: ID type_mark	{$$=createNameAndTypeList(createNameAndType($1,$2));}
| id_list_2_or_more type_mark	{$$=convertIdListToNameAndTypeList($1,$2);}
;

id_list_2_or_more: ID ',' ID	{$$=addToIdList(createIdList(createId($1)),createId($3));}
| id_list_2_or_more ',' ID		{$$=addToIdList($1,createId($3));}
| id_list_2_or_more ',' error	{$$=$1;}
;

%%
/* —екци€ пользовательского кода */

void yyerror (const char *s)
{
	printf ("BISON near line %d: %s\n", yylloc.first_line, s);
	if(syntax_errors_logged >= MAX_SYNTAX_ERRORS)
	{
		return;
	}
	else if(syntax_errors_logged >= MAX_SYNTAX_ERRORS-1)
	{
		char too_namy_errors [] = "Cannot recover from errors, abort compilation";
		s = too_namy_errors;
		printf ("BISON: %s\n", s);
	}
	// append allocated string to array
	syntax_errors[syntax_errors_logged] = (char*)malloc(strlen(s)+1);
	strcpy(syntax_errors[syntax_errors_logged], s);
	++syntax_errors_logged;

	// YYABORT;
}

// переменные, глобальные дл€ анализатора
struct NIdList* currentFeatureClients;

