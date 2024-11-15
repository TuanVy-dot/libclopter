#ifndef CLOPTER_H

#define CLOPTER_H

/*
 * clopter or commandline opter
 * A library for handling commandline options
 * Extensible and Ease of use is key!
 * 
 * Easily create and parse args
 * Simple guide:
 * Create parser_t* with parser_create
 * Create your arguements with parser_add_*****
 * Create Args* with parser_parse_args
 * Access by either getter functions(slower) or directly by index in Args
 * (order preserved)
 */

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
/* Create and free parsers */
parser_t *parser_create(void);
void parser_destroy(parser_t *parser);

/* Add arguements to a parser */
int parser_add_positional(parser_t *parser, const char *name);
int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, int n_identifiers);
int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, int n_identifiers,
                     unsigned int nargs, const char **default_values);

/* Arguements parsing and freeing */
Args *parser_parse_args(parser_t *parser, int argc, const char *argv[]);
void args_destroy(Args *args);

/* Getters */

/* Get index of an arg within parser with name */
int parser_search_positional(parser_t *parser, const char *name);
int parser_search_flag(parser_t *parser, const char *name);
int parser_search_group(parser_t *parser, const char *name);

/* get value of an arg within the Args struct with name */
const char *args_get_positional(Args *args, char *name);
_Bool args_get_flag(Args *args, char *name);
const char **args_get_group(Args *args, char *name);

#endif
