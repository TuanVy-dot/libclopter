#include "../api/clopter.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [options] [filename]\n", argv[0]);
        return 1;
    }
    parser_t *parser = parser_create();
    parser_add_positional(parser, "filename");
    const char *append_identifiers[] = {"-a", "--append"};
    /* That 2 is call n_idenfifiers, pretty annoying but needed */
    parser_add_flag(parser, "append", append_identifiers, 2);
    Args *args = parser_parse_args(parser, argc, argv);
    const char *filepath = args_get_positional(args, "filename");
    _Bool append = args_get_flag(args, "append");
    if (args -> remain > 0) {
        const char *leftover = (args -> leftovers)[0];
        printf("Undefined option: %s\n", leftover);
        printf("Usage: %s [options] [filename]\n", argv[0]);
        return 1;
    }
    /* Free */
    parser_destroy(parser);
    args_destroy(args);
    FILE *file;
    if (append) {
        file = fopen(filepath, "a");
    } else {
        file = fopen(filepath, "w");
    }
    int c;
    while ((c = getchar()) != EOF) {
        putc(c, file);
    }
    fclose(file);
    return 0;
}
