#ifndef GETTER_H

#define GETTER_H

/* Getter functions */
/* Use to search for arguements or get values */

#include "parser_n_arg.h"
#include "parsing.h"

/* Searcher */
int parser_search_positional(parser_t *parser, const char *name);
int parser_search_flag(parser_t *parser, const char *name);
int parser_search_group(parser_t *parser, const char *name);

/* Getter */
const char *args_get_positional(Args *args, char *name);
_Bool args_get_flag(Args *args, char *name);
const char **args_get_group(Args *args, char *name);

#endif
