%{ 
// #include <iostream> 
// using namespace std; --> we use printf() only
extern int yylex(); 
%} 
%option noyywrap 
%option neverinteractive

%% 

[ \t\n] ; 
[0-9]+\.[0-9]+ { cout << "Found a floating-point number:" << yytext << endl; } 
[0-9]+ { cout << "Found an integer:" << yytext << endl; } 
[a-zA-Z0-9]+ { cout << "Found a string: " << yytext << endl; } 

%% 

int main(int, char**) { 
// lex through the input: 
while (yylex()); 
}
