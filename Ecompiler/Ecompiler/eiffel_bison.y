%{
/*ѕролог*/
#include "bisonFunctions.h"
	
/* более подробные собщени€ об ошибках */
#define YYERROR_VERBOSE 1
	
// ‘лаг дл€ управлени€ контекстом Flex`а
int global_LF_enabled = false;

void yyerror (char const *s);

extern int yylex();

struct NClassList* root;

%}

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
struct NAccess* access_struct;
struct NRef* ref_struct;
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

// struct * _struct;
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
%type <access_struct> access
%type <ref_struct> ref
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


/* более подробные собщени€ об ошибках */
%define parse.error verbose

%token <Int> INT_VAL
%token <Real> REAL_VAL
%token <Char> CHAR_VAL
%token <String> STRING_VAL
%token <Bool> BOOL_VAL
%token <String> ID
%token ASSIGN IF LOCAL DO END ELSEIF THEN ELSE CLASS FROM UNTIL LOOP CREATE FEATURE RESULT CURRENT PRECURSOR INHERIT REDEFINE
%token ARRAY INTEGER REAL CHARACTER STRING BOOLEAN


%left ';' LF
%left '[' ']'
%left IMPLIES
%left OR OR_ELSE XOR
%left AND AND_THEN
%left EQUALS NOT_EQUALS LESS GREATER LESS_OR_EQUAL GREATER_OR_EQUAL
%left '+' '-'
%left '*' '/'
%left '^'
%left NOT UPLUS UMINUS
%left '.'
%nonassoc ')'

%%

program : class_list	{root = $1;}
;

class_list: class	{$$=createClassList($1);}
| class_list class	{$$=addToClassList($1,$2);}
;

class: CLASS ID inheritance_opt creation_list_opt feature_clauses_opt END	{$$=createClass($2,$3,$4,$5);}
;

inheritance_opt: /*empty*/	{$$=0;}
| inheritance_list			{$$=$1;}
;
inheritance_list: INHERIT inherit_from_class {$$=createInheritFromClassList($2);}
| inheritance_list inherit_from_class		{$$=addInheritFromClassList($1,$2);}
;
inherit_from_class: ID /*rename_opt*/ /*undefine_opt*/ redefine_opt END	{$$=createInheritFromClass($1,$2);}

redefine_opt: /*empty*/	{$$=0;}
| redefine				{$$=$1;}
;
redefine: REDEFINE ID		{$$=createIdList(createId($2));}
| REDEFINE id_list_2_or_more	{$$=$2;}
;

creation_list_opt: /*empty*/	{$$=0;}
| creation_list					{$$=$1;}
;
creation_list: CREATE ID	{$$=createIdList(createId($2));}
| creation_list ',' ID		{$$=addToIdList($1,createId($3));}
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
;

attributes: vars_declaration {$$=createAttributesFrom($1);}
;



access: ID		{$$=createAccess(IdA, $1, 0);}
| 		ID '(' expr_list_opt ')' {$$=createAccess(IdA, $1, $3);}
		/* следующие нельз€ вызывать через точку: */
| 		RESULT	{$$=createAccess(ResultA, 0, 0);}
| 		CURRENT	{$$=createAccess(CurrentA, 0, 0);} // нельз€ сочетать: CURRENT '[' <i> ']'
|		PRECURSOR	{$$=createAccess(PrecursorA, 0, 0);}
|		PRECURSOR '(' expr_list_opt ')' {$$=createAccess(PrecursorA, 0, $3);}
|		PRECURSOR '{' ID '}' {$$=createAccess(PrecursorA, $3, 0);}
|		PRECURSOR '{' ID '}' '(' expr_list_opt ')' {$$=createAccess(PrecursorA, $3, $6);}

;

ref: access				{$$=createRef(0,$1,0);}
| ref '.' access		{$$=createRef($1,$3,0);}
| ref '[' expr ']' 		{$$=createRef($1,0,$3);}
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

stmt: _LF_ON_ CREATE ref stmt_sep _LF_OFF_	{$$=createStmt(CreateSt,$3);}
| _LF_ON_ assign_stmt _LF_OFF_		{$$=createStmt(AssignSt,$2);}
| _LF_ON_ ref stmt_sep _LF_OFF_	{$$=createStmt(RefSt,$2);}
| if_stmt			{$$=createStmt(IfSt,$1);}
| from_loop			{$$=createStmt(LoopSt,$1);}
;

stmt_list: stmt 	{$$=createStmtList($1);}
| stmt_list stmt 	{$$=addToStmtList($1, $2);}
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

expr: INT_VAL	{$$=createIntConstExpr($1);}
| REAL_VAL		{$$=createRealConstExpr($1);}
| CHAR_VAL		{$$=createCharConstExpr($1);}
| STRING_VAL	{$$=createStringConstExpr($1);}
| BOOL_VAL		{$$=createBoolConstExpr($1);}
| ref			{$$=createRefExpr($1); }
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

expr_list: expr			{$$=createExprList($1);}
| expr_list ',' expr 	{$$=addToExprList($1, $3);}
;

expr_list_opt: expr_list	{$$=($1);}
| /*empty*/				{$$=createExprList(0);}
;

assign_stmt: ref ASSIGN expr stmt_sep {$$=createAssignStmt($1, $3);}
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


from_loop: FROM stmt_list_opt UNTIL expr LOOP stmt_list END	{$$=createFromLoop($2, $4, $6);}
;


routine: ID param_list_0_or_more return_value_opt local_vars_opt routine_body	{$$=createFeature($1,$2,$3,$4,$5);}
| ID return_value local_vars routine_body	{$$=createFeature($1,0,$2,$3,$4);}
| ID  return_value  routine_body	{$$=createFeature($1,0,$2,0,$3);}
| ID  local_vars routine_body	{$$=createFeature($1,0,createType(VoidV),$2,$3);}
| ID   routine_body				{$$=createFeature($1,0,createType(VoidV),0,$2);}
;

routine_body: DO stmt_list_opt END	{$$=$2;}
;

param_list_0_or_more: '(' param_list ')'	{$$=$2;}
| '(' ')'				{$$=createNameAndTypeList(0);}
;

param_list: param		{$$=createNameAndTypeList($1);}
| param_list ';' param	{$$=addToNameAndTypeList($1,$3);}
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
;

vars_declaration: ID type_mark	{$$=createNameAndTypeList(createNameAndType($1,$2));}
| id_list_2_or_more type_mark	{$$=convertIdListToNameAndTypeList($1,$2);}
;

id_list_2_or_more: ID ',' ID	{$$=addToIdList(createIdList(createId($1)),createId($3));}
| id_list_2_or_more ',' ID		{$$=addToIdList($1,createId($3));}
;

/*
error_token: INT_INTERVAL	{ yyerror("Forbidden token: INT_INTERVAL"); YYERROR;}
		   | CHAR_INTERVAL	{ yyerror("Forbidden token: CHAR_INTERVAL");YYERROR;}
		   ;
*/
%%
/*—екци€ пользовательского кода*/

void yyerror (char const *s)
{
  // fprintf (stderr, "%s\n", s);
}	

// переменные, глобальные дл€ анализатора
// struct NClass* currentClass = NULL;
struct NIdList* currentFeatureClients;
// struct NType* currentType;

