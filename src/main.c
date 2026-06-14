#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "ncscanner.h"

const char *ncfile = NULL;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <file>\n", argv[0]);
        return 1;
    }

    ncfile = argv[1];
    char *source = NULL;

    if (read_file(ncfile, &source) != 0) {
        printf("error: failed to read file\n");
        return 1;
    }

    struct TokenList tokens;

    if (tokenize(source, &tokens) != 0) {
        printf("errors encountered during tokenization\n");
        return 1;
    }

    free(source);
    token_list_free(&tokens);

    return 0;
}
