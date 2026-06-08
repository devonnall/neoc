#ifndef CM_TOKEN_H
#define CM_TOKEN_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_STRING,
    TOKEN_BOOL,
    TOKEN_FOR,
    TOKEN_IN,
    TOKEN_DO,
    TOKEN_END,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_SCOPE,
    TOKEN_RANGE,
    TOKEN_EQUAL_EQUAL,
    TOKEN_PLUS_PLUS,
    TOKEN_PLUS_EQUAL,
    TOKEN_MINUS_MINUS,
    TOKEN_MINUS_EQUAL,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EQUAL,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_STRING_LITERAL,
    TOKEN_NUMBER,
    TOKEN_IDENT,
    TOKEN_ERROR
} token_t;

typedef struct {
    token_t type;
    const char *text;
    int line;
} Token;

typedef struct {
    Token *tokens;
    int length;
    int capacity;
} TokenList;

#define YY_USER_ACTION update_lc();

void update_lc();
Token * make_token(token_t type);

#endif // CM_TOKEN_H
