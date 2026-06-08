#ifndef DUSTY_SCANNER_H
#define DUSTY_SCANNER_H

#include <stdbool.h>

struct dytext {
        char *text;
        int length;
};

struct scanner {
        const char *source;
        int cursor;
        int line;
        int column;
};

enum token_type {
        TOKEN_EOF = 0,
        TOKEN_INT,
        TOKEN_STRING,
        TOKEN_NUMBER,
        TOKEN_COLON,
        TOKEN_SEMICOLON,
        TOKEN_EQUAL,
        TOKEN_STRING_LITERAL,
        TOKEN_IDENT,
        TOKEN_SKIP,
        TOKEN_ERROR
};

struct token {
        enum token_type type;
        int start;
        int length;
        const char *semantic_value;
};

enum token_type get_token(struct scanner *dy_sacnner, struct dytext *text);
struct token make_token(enum token_type type, char *dytext);
void tokens_append(struct token dytoken);

extern const char *dyfile;
extern bool errors;

#endif // DUSTY_SCANNER_H
