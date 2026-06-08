%{
#include <stdio.h>
#include "token.h"
%}

DIGIT [0-9]
LETTER [a-zA-Z]
ALPHANUM [a-zA-Z0-9\_]

%%
" "|"\t"|"\r"|"\n"     {}
\#[^\n]*             {}
int                    { return TOKEN_INT; }
float                  { return TOKEN_FLOAT; }
double                 { return TOKEN_DOUBLE; }
string                 { return TOKEN_STRING; }
bool                   { return TOKEN_BOOL; }
for                    { return TOKEN_FOR; }
in                     { return TOKEN_IN; }
do                     { return TOKEN_DO; }
end                    { return TOKEN_END; }
true                   { return TOKEN_TRUE; }
false                  { return TOKEN_FALSE; }
null                   { return TOKEN_NULL; }
\:\:                   { return TOKEN_SCOPE; }
\.\.\.                 { return TOKEN_RANGE; }
\=\=                   { return TOKEN_EQUAL_EQUAL; }
\+\+                   { return TOKEN_PLUS_PLUS; }
\+\=                   { return TOKEN_PLUS_EQUAL; }
\-\-                   { return TOKEN_MINUS_MINUS; }
\-\=                   { return TOKEN_MINUS_EQUAL; }
\+                     { return TOKEN_PLUS; }
\-                     { return TOKEN_MINUS; }
\=                     { return TOKEN_EQUAL; }
\(                     { return TOKEN_LPAREN; }
\)                     { return TOKEN_RPAREN; }
\[                     { return TOKEN_LBRACKET; }
\]                     { return TOKEN_RBRACKET; }
\:                     { return TOKEN_COLON; }
\,                     { return TOKEN_COMMA; }
\"[^\n\"]*\"           { return TOKEN_STRING_LITERAL; }
\-?{DIGIT}+(\.?{DIGIT}+)? { return TOKEN_NUMBER; }
{LETTER}{ALPHANUM}*    { return TOKEN_IDENT; }
.                      { return TOKEN_ERROR; }
%%

int yywrap() {
    return 1;
}

