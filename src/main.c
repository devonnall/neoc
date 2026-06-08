#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"
#include "scanner.h"

const char *dyfile = NULL;
bool errors = false;

int main(int argc, char **argv) {
        if (argc < 2) {
                printf("usage: %s <file>\n", argv[0]);
                return 1;
        }

        dyfile = argv[1];
        const char *source = NULL;
        struct dytext text = {0};

        if (read_file(dyfile, &source) != 0) {
                printf("error: failed to read file\n");
                return 1;
        }

        struct scanner dy_scanner = {
                .source = source,
                .cursor = 0,
                .line = 1,
                .column = 1
        };

        for (;;) {
                enum token_type type = get_token(&dy_scanner, &text);
                if (type == TOKEN_EOF) break;
                if (type == TOKEN_SKIP) continue;
                printf("%u: %s\n", type, text.text);
        }

        return 0;
}
