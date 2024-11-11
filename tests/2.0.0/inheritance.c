#include "../api/clopter.h"
#include <stdio.h>

int main(int argc, const char *argv[]) {
    parser_t *baseP = parser_create();
    parser_add_positional(baseP, "common arg");
    parser_add_flag(baseP, "verbose", (const char*[]){"-v", "--verbose"}, 2);

    parser_t *parser1 = parser_inherit(baseP);
    parser_add_positional(parser1, "p1 specific");
    parser_t *parser2 = parser_inherit(baseP);
    parser_add_flag(parser2, "p2 specific", (const char*[]){"-a"}, 1);

    Args *arg1 = parser_parse_args(parser1, argc, argv);
    Args *arg2 = parser_parse_args(parser2, argc, argv);

    printf("arg1:\n");
    printf("common: %s\nverbose: %d\np1_specific: %s\np2_specific: %d\n",
            args_get_positional(arg1, "common arg"), args_get_flag(arg1, "verbose"), 
            args_get_positional(arg1, "p1 specific"), args_get_flag(arg1, "p2 specific"));
    printf("arg2:\n");
    printf("common: %s\nverbose: %d\np1_specific: %s\np2_specific: %d\n",
            args_get_positional(arg2, "common arg"), args_get_flag(arg2, "verbose"), 
            args_get_positional(arg2, "p1 specific"), args_get_flag(arg2, "p2 specific"));
    return 0;
}
