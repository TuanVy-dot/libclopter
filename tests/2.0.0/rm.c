#include "clopter.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[]) {
    parser_t *parser = parser_create();
    parser_add_positional(parser, "hello");
    int index = parser_search_positional(parser, "hello");
    printf("%d\n", index);
    printf("%d\n", parser_remove_positional(parser, "hello"));
    index = parser_search_positional(parser, "hello");
    printf("%d\n", index);
    return 0;
}
