#include <stdio.h>
#include <stdlib.h>
#include "token.h"

extern FILE *yyin;
extern int yylex();
extern char *yytext;

int current_line = 1;
int current_column = 1;

void update_lc() {
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            current_line++;
            current_column = 1;
        } else {
            current_column++;
        }
    }
}

Token * make_token(token_t type) {
    // Token token = {
    //     .type = type,
    //     .text = yytext,
    //     .line = current_line
    // };

    Token *token = (Token*)malloc(sizeof(Token));
    token->type = type;
    token->text = yytext;
    token->line = current_line;
    return token;
}

void TokenList_append(TokenList *tokens, Token *token) {
    if (tokens->length >= tokens->capacity) {
        tokens->tokens = (Token*)realloc(tokens->tokens, tokens->capacity * 2);
    }
    tokens->tokens[tokens->length++] = *token;
}

int main(int argc, char **argv) {
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("error: failed to open \"%s\"\n", argv[1]);
        return 1;
    }

    fseek(yyin, 0, SEEK_END);
    long length = ftell(yyin);
    fseek(yyin, 0, SEEK_SET);

    int estimate = length / 3;

    TokenList tokens = {
        .tokens = malloc(estimate * sizeof(Token)),
        .length = 0,
        .capacity = estimate
    };

    while (1) {
        token_t token_type = yylex();
        if (token_type == TOKEN_ERROR) {
            printf("error: line %d, column %d\n%s", current_line, current_column, yytext);
            return 1;
        } else if (token_type == TOKEN_EOF) {
            break;
        }
        // printf("%s ", yytext);
        Token *token = make_token(token_type);
        // printf("%s\n", token.text);
        TokenList_append(&tokens, token);
    }
    for (int i = 0; i < tokens.length; i++) {
        printf("%s ", tokens.tokens[i].text);
    }
    printf("\n");
    return 0;
}

