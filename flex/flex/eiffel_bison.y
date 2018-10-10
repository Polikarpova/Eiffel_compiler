%{

	//Пролог

%}

Секция объявлений
%union {
int Int;
char Char;
char *String;
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
%token <> REAL
%token <Char> CHAR
%token <String> STRING

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
%lefy '^'
%left OLD NOT UPLUS UMINUS
%left '.'
%nonassoc ')'

%%

//может и не так, но зато мы про него не забудем :D
program : class_list
;

class_list: class
| class_list class
;

...

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

%%

{/*Секция пользовательского кода*/}