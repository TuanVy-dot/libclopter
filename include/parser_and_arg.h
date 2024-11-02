#ifndef CLOPTER_H

#define CLOPTER_H

enum TypeCodes {
    TYPE_INT, TYPE_FLOAT, TYPE_STR
};
typedef enum TypeCodes typecode_t;

typedef struct arg_positional_t arg_positional_t;
typedef struct arg_flag_t arg_flag_t;
typedef struct arg_group_t arg_group_t;
typedef struct parser_t parser_t;

struct parser_t {
    const char *description;
    arg_positional_t **positional_args;
    int positional_args_count;
    arg_flag_t **flag_args;
    int flag_args_count;
    arg_group_t **group_args;
    int group_args_count;
};

struct arg_positional_t {
    const char *name;
    const char *desc;
    typecode_t type;
    const void *default_value;
};

struct arg_flag_t {
    const char *name;
    const char **identifiers;
    const char *desc;
};

struct arg_group_t {
    const char *name;
    const char **identifiers;
    const char *desc;
    unsigned int nargs;
    typecode_t type;
    const void *default_values;
};

parser_t *parser_create(const char *description);
int parser_add_positional(parser_t *parser, const char *name, const char *desc,
                          const typecode_t type, const void *default_value);
int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, const char *desc);
int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, const char *desc, unsigned int nargs,
                     typecode_t type, const void *default_values);

#endif
