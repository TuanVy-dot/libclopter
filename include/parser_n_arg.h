#ifndef CLOPTER_H

#define CLOPTER_H

/*
 * Define parsers and arguements
 * With functions for creations and removals
 */

typedef struct arg_positional arg_positional;
typedef struct arg_flag arg_flag;
typedef struct arg_group arg_group;
typedef struct Parser Parser;

/* Opaque Parser type */
typedef struct parser_t *parser_t;

struct Parser {
    arg_positional **positional_args;
    int positional_args_count;
    arg_flag **flag_args;
    int flag_args_count;
    arg_group **group_args;
    int group_args_count;
};

struct arg_positional {
    const char *name;
};

struct arg_flag {
    const char *name;
    const char **identifiers;
    int n_identifiers;
};

struct arg_group {
    const char *name;
    const char **identifiers;
    int n_identifiers;
    unsigned int nargs;
    const char **default_values;
};

parser_t *parser_create(void);
void parser_destroy(parser_t *parser);
int parser_add_positional(parser_t *parser, const char *name);
int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, int n_identifiers);
int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, int n_identifiers,
                     unsigned int nargs, const char **default_values);

#endif
