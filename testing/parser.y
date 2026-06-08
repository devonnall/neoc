%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *msg);
int yylex(void);
%}

%token NUMBER NEWLINE
%token PLUS MINUS TIMES DIVIDE
%token LPAREN RPAREN
%token INVALID

%left PLUS MINUS
%left TIMES DIVIDE
%right UMINUS


%%

input: 
     expr NEWLINE   { printf("%d\n", $1); }
     ;

expr:
    expr PLUS term  { $$ = $1 + $3; }
    | expr MINUS term  { $$ = $1 - $3; }
    | term
    ;

term:
    term TIMES factor  { $$ = $1 * $3; }
    | term DIVIDE factor  { $$ = $1 / $3; }
    | factor
    ;
    
factor:
      MINUS factor  { $$ = -$1; }
      | LPAREN expr RPAREN  { $$ = $2; }
      | NUMBER  
      ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Parse error: %s\n", msg);
}
