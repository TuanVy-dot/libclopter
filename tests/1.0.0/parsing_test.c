#include "logger.h"
#include "clopter.h"
#include <stdbool.h>
#include <stdio.h>

/*
 * Testing with log usage, don't forget to link against the debug version
 * And create the logs directory
 * This is my logging library, if interested, see liblogger repo
 */

LOGGER *CLOPTER;

int main(int argc, const char *argv[]) {
    FILE *log = fopen("logs/test.log", "w");
    CLOPTER = logger_create("CLOPTER", log, DEFAULT_LOG_FORMAT, TRACE);
    logger_level_color_default();

    parser_t *parser = parser_create();
    if (!parser) {
        perror("Error: ");
        return 1;
    }
    const char *help_indentifiers[] = {"-h"};
    parser_add_flag(parser, "help", help_indentifiers, 1);
    const char *out_iden[] = {"-o", "--output"};
    const char *out_default[] = {"a.out"};
    parser_add_group(parser, "output", out_iden, 2, 1, out_default);
    parser_add_positional(parser, "filename");
    Args *args = parser_parse_args(parser, argc, argv);
    if (!args) {
        perror("Error: ");
        return 1;
    }

    printf("%d\n", parser_search_positional(parser, "filename"));

    printf("Help: %s\n", (args_get_flag(args, "help")) ? "true" : "false");
    printf("output: %s\n", args_get_group(args, "output")[1]);
    printf("filename: %s\n", args_get_positional(args, "filename"));
    int lim = args -> remain;
    for (int i = 0; i < lim; i++) {
        printf("Leftovers_%d: %s\n", i, (args -> leftovers)[i]);
    }

    return 0;
}
