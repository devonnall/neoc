#include <stdio.h>
#include <stdlib.h>
#include "ncscanner.h"
#include "ncparser.h"

static void
add_child(struct Node *parent_node) {
    if (parent_node->children == NULL) {
        parent_node->children = malloc(
    }
}

static void
parse_stmt(struct Parser *parser) {
    switch (parser->list[parser->pos].type) {
        case TOKEN_IF:
            parse_ifstmt(parser);
            break;
    }
}

int
parse(struct TokenList *list, struct Tree *ast) {
    struct Parser parser = {
        .list = list,
        .ast = ast,
        .bol = list->tokens,
        .pos = 0,
        .ntokens = list->count
    };

    struct Node *root = malloc(sizeof(Node));
    root->

    for (int i = 0; i < parser.list->count; i++) {
        parse_stmt(&parser);
    }
    return 0;
}


