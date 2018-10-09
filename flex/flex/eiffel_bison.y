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

%token <Int> INT
%token <Char> CHAR
%token <String> STRING

%type if_stmt
%type loop_stmt

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

Секция правил грамматики

%%

Секция пользовательского кода