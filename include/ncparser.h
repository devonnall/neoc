#ifndef NEOC_PARSER_H
#define NEOC_PARSER_H

struct Parser {
    struct TokenList *list;
    struct Tree *ast;
    struct Token *bol;
    int pos;
    int ntokens;
};

enum NodeType {
    NODE_IFSTMT, NODE_FN_STMT, NODE_FORSTMT, NODE_WHILESTMT, 
};

struct Node {
    struct Token *token;
    struct Node *children;
    int nchidlren;
};

struct Tree {
    struct Node *parent;
};

int parse(struct TokenList *list, struct Tree *ast);

#endif // NEOC_PARSER_H
