#include <stdio.h>
#include <stdlib.h>

extern int yyparse(void);

int main() {
    printf("> ");
    fflush(stdout);

    int result = yyparse();
    return result;
}
