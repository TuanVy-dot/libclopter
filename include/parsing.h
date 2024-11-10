#ifndef PARSING_H

#define PARSING_H

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

#endif
