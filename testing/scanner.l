%{
#include "parser.tab.h"
%}

%%

[0-9]+(\.[0-9]+)? { return NUMBER; }
"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return TIMES; }
"/"               { return DIVIDE; }
"("               { return LPAREN; }
")"               { return RPAREN; }
[ \t]             {}
"\n"              { return NEWLINE; }
.                 { return INVALID; }

%%

int yywrap(void) { return 1; }
