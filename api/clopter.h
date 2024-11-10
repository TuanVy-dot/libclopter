#ifndef CLOPTER_H

#define CLOPTER_H

#include <stdbool.h>

/* parser_t is a hidden type for Parser */
typedef struct parser_t parser_t;

struct Args {
    const parser_t *const Parser;
    const char **positional;
    _Bool *flags;
    const char ***groups;
    const char **leftovers;
    const int remain;
};
typedef struct Args Args;

/* Parsers amd arguements creation */
parser_t *parser_create(const char *description);
void parser_destroy(parser_t *parser);
int parser_add_positional(parser_t *parser, const char *name, const char *desc,
                          const void *default_value);
int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, int n_identifiers,
                    const char *desc);
int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, int n_identifiers,
                     const char *desc, unsigned int nargs,
                     const void *default_values);

/* Arguements parsing */
Args *parser_parse_args(parser_t *parser, int argc, const char *argv[]);
void args_destroy(Args *args);

/* Getters */
int parser_search_positional(parser_t *parser, const char *name);
int parser_search_flag(parser_t *parser, const char *name);
int parser_search_group(parser_t *parser, const char *name);

const char *args_get_positional(Args *args, char *name);
_Bool args_get_flag(Args *args, char *name);
const char **args_get_group(Args *args, char *name);

#endif
