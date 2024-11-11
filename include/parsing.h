#ifndef PARSING_H

#define PARSING_H

/* Define Args struct and parsing functions */

#include "parser_n_arg.h"

struct Args {
    parser_t *Parser;
    const char **positional;
    _Bool *flags;
    const char ***groups;
    const char **leftovers;
    int remain;
};
typedef struct Args Args;

Args *parser_parse_args(parser_t *parser, int argc, const char *argv[]);
void args_destroy(Args *args);

#endif
