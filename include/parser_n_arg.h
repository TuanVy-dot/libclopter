#ifndef CLOPTER_H

#define CLOPTER_H

enum TypeCodes {
    TYPE_INT, TYPE_FLOAT, TYPE_STR
};
typedef enum TypeCodes typecode;

typedef struct arg_positional arg_positional;
typedef struct arg_flag arg_flag;
typedef struct arg_group arg_group;
typedef struct Parser Parser;

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
    const void *default_value;
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
    const void *default_values;
};

parser_t *parser_create(void);
void parser_destroy(parser_t *parser);
int parser_add_positional(parser_t *parser, const char *name, 
                          const void *default_value);
int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, int n_identifiers);
int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, int n_identifiers,
                     unsigned int nargs, const void *default_values);

#endif
