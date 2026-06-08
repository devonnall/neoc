#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"

void dy_print_error(struct scanner *dyscanner, const char *msg) {
        if (!errors) {
                errors = true;
        }

        printf("%s:%d:%d: error: %s\n",
                dyfile,
                dyscanner->line,
                dyscanner->column,
                msg);
}

int iswhitespace(char ch) {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0') 
                return 1;
        
        return 0;
}

int iswordchar(char ch) {
        if (isalnum(ch) || ch == '_') {
                return 1;
        }
        return 0;
}

int match(const char *s1, const char *s2, size_t n) {
        char after = *(s2 + n);
        if (strncmp(s1, s2, n) == 0 && iswhitespace(after))
                return 1;

        return 0;
}

void advance(struct scanner *dyscanner, size_t n) {
        for (size_t i = 0; i < n; i++) {
                dyscanner->cursor++;
                if (dyscanner->source[dyscanner->cursor] == '\n') {
                        dyscanner->line++;
                        dyscanner->column = 1;
                } else if (dyscanner->source[dyscanner->cursor] == '\0') {
                        break;
                } else {
                        dyscanner->column++;
                }
        }
}

int get_identifier(struct scanner *dyscanner) {
        int start_pos = dyscanner->cursor;
        const char *start = &dyscanner->source[start_pos];
        while (iswordchar(*start++)) {
                advance(dyscanner, 1);
        }
        return dyscanner->cursor - start_pos;
}

void recover(struct scanner *dyscanner) {
        const char *ch = &dyscanner->source[dyscanner->cursor];
        while (*ch != ';' && *ch != '\n' && *ch != ' ' 
                && *ch != '\t' && *ch != ':' && *ch != '\0') {
                advance(dyscanner, 1);
                ch = &dyscanner->source[dyscanner->cursor];
        }
}

int get_number(struct scanner *dyscanner, bool *syntax_error) {
        int start_pos = dyscanner->cursor;
        // const char *ch = &dyscanner->source[start_pos];

        while (isdigit(dyscanner->source[dyscanner->cursor])) {
                advance(dyscanner, 1);
        }

        if (isalpha(dyscanner->source[dyscanner->cursor])) {
                recover(dyscanner);
                *syntax_error = true;
                dy_print_error(dyscanner, "invalid number");
        }

        return dyscanner->cursor - start_pos;
}

enum token_type get_token(struct scanner *dyscanner, struct dytext *text) {
        const char *start = &dyscanner->source[dyscanner->cursor];
        enum token_type type;
        bool syntax_error = false;

        memset(text->text, 0, text->length);

        switch(*start) {
        case ' ': case '\t': case '\r': case '\n':
                advance(dyscanner, 1); 
                type = TOKEN_SKIP;
                break;
        case 'i':
                if (match(start, "int", 3)) {
                        text->text = realloc(text->text, 4);
                        text->length = 3;
                        strcpy(text->text, "int");
                        advance(dyscanner, 3);
                        type = TOKEN_INT;
                } else {
                        int len = get_identifier(dyscanner);
                        text->text = realloc(text->text, len+1);
                        text->length = len;
                        strncpy(text->text, start, len);
                        type = TOKEN_IDENT;
                }
                break;
        case ':':
                text->text = realloc(text->text, 2);
                text->text[0] = ':';
                text->text[1] = '\0';
                text->length = 1;
                advance(dyscanner, 1);
                type = TOKEN_COLON;
                break;
        case ';':
                text->text = realloc(text->text, 2);
                text->text[0] = ';';
                text->text[1] = '\0';
                text->length = 1;
                advance(dyscanner, 1);
                type = TOKEN_SEMICOLON;
                break;
        case  '=':
                text->text = realloc(text->text, 2);
                text->text[0] = '=';
                text->text[1] = '\0';
                text->length = 1;
                advance(dyscanner, 1);
                type = TOKEN_EQUAL;
                break;
        case '\0':
                type = TOKEN_EOF;
                break;
        default:
                if (isalpha(*start)) {
                        int len = get_identifier(dyscanner);
                        text->text = realloc(text->text, len+1);
                        text->length = len;
                        strncpy(text->text, start, len);
                        type = TOKEN_IDENT;
                } else if (isdigit(*start)) {
                        int len = get_number(dyscanner, &syntax_error);
                        text->text = realloc(text->text, len+1);
                        text->length = len;
                        strncpy(text->text, start, len);

                        if (syntax_error)
                                type = TOKEN_ERROR;
                        else
                                type = TOKEN_NUMBER;
                } else {
                        dy_print_error(dyscanner, "invalid character");
                        type = TOKEN_ERROR;
                }
                break;
        }

        return type;
}
