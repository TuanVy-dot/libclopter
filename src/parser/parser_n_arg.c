#include "parser_n_arg.h"
#include "log_api.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* parser_imp is used to name parser implementation type which is Parser
 * to distinguish with parser_t, the opaque */

static int push(void *val, void ***stack, int *top);

/* Push function for arguements addition,
 * assume the stack is always in minimal size */
static int push(void *val, void ***stack, int *top) {
    /* assuming the stack is legit which I'll try my best to,
     * NULL every uninitiallized, it is safe to just realloc */
    logger_tracef("enter push function with parameters:\n- val = %p\n- stack = %p\n- top = %p", val, stack, top);
    void **temp = realloc(*stack, (*top + 1)*sizeof(void *));
    logger_tracef("memory reallocation of *stack from %d to %d (bytes) and assign he address to temp with address %p", *top*sizeof(void*), (*top + 1)*sizeof(void*), temp);
    logger_debugf("memory reallocation from %d ptrs to %d ptrs", *top, *top + 1);
    if (!temp) {
        logger_error("reallocation failed");
        logger_trace("return with code 1");
        return 1;
    }
    *stack = temp;
    logger_trace("reassign temp to stack(in case of memory movement");
    (*stack)[(*top)++] = val;
    logger_debugf("set stack at %d to val and increment top to %d", *top - 1, *top);
    logger_info("push whatever given to the stack(assume type match)");
    logger_trace("return with code 0");
    return 0;
}

/* Parsers functions */
parser_t *parser_create(void) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));
    logger_debugf("memory allocation with size %d(of parser_t) to variable of name 'parser'", sizeof(Parser));

    if (!parser) {
        logger_error("memory allocation failed");
        logger_info("return with NULL");
        return NULL;
    }

    logger_info("assign NULL to all arrays and 0 to counts");
    parser -> positional_args = NULL;
    parser -> flag_args = NULL;
    parser -> group_args = NULL;
    parser -> positional_args_count = parser -> flag_args_count\
                                    = parser -> group_args_count = 0;
    logger_trace("return with parser");
    return (parser_t*)parser;
}

void parser_destroy(parser_t *parser) {
    Parser *parser_imp = (Parser *)parser;
    int posc = parser_imp -> positional_args_count;
    arg_positional **positional_args = parser_imp -> positional_args;
    int flgc = parser_imp -> flag_args_count;
    arg_flag **flag_args = parser_imp -> flag_args;
    int grpc = parser_imp -> group_args_count;
    arg_group **group_args = parser_imp -> group_args;
    if (positional_args) {
        while (posc--) {
            free(positional_args[posc - 1]);
        }
        free(positional_args);
    }
    if (flag_args) {
        while (flgc--) {
            free(flag_args[flgc - 1]);
        }
        free(flag_args);
    }
    if (group_args) {
        while (grpc--) {
            free(group_args[grpc - 1]);
        }
        free(group_args);
    }
    free(parser_imp);
}

/* arguements addition */
int parser_add_positional(parser_t *parser, const char *name) {
    logger_tracef("enter parser_add_positional with parameters:\n"
            "- parser = %p\n- name = %p\n", parser, name);
    arg_positional *arg = (arg_positional*)malloc(sizeof(arg_positional));
    logger_debugf("memory allocation with size %d(of arg_positional) and assign to variable 'arg' at address %p", sizeof(arg_positional), arg);
    if (!arg) {
        logger_error("memory allocation failed");
        logger_trace("return with code 1");
        return 1;
    }

    if (!name) {
        free(arg);
        logger_debug("expected non-NULL address for 'name', exit");
        logger_tracef("free arg(%p) and return with code 1", arg);
        return 1; // name is required
    }
    arg -> name = name;

    logger_info("push arg into parser positional_args array");
    Parser *parser_imp = (Parser*)parser;
    int i = push(
            arg, 
            (void ***)&parser_imp -> positional_args, 
            &parser_imp -> positional_args_count
            );

    if (i != 0) {
        logger_error("push failed");
        logger_tracef("free arg(%p) and return with code 1", arg);
        free(arg);
        return 1;
    }
    logger_trace("return with code 0");
    return 0;
}

int parser_add_flag(parser_t *parser, const char *name,
                    const char **identifiers, int n_identifiers) {
    logger_tracef("enter parser_add_flag with parameters:\n"
            "- parser = %p\n- name = %p\n- identifiers = %p\n- n_identifiers = %d\n", 
            parser, name, identifiers, n_identifiers);
    
    arg_flag *arg = (arg_flag*)malloc(sizeof(arg_flag));
    logger_debugf("memory allocation with size %d(of arg_flag) and assign to variable 'arg' at address %p", 
            sizeof(arg_flag), arg);
    if (!arg) {
        logger_error("memory allocation failed");
        logger_trace("return with code 1");
        return 1;
    }

    if (!name || !identifiers) {
        free(arg);
        logger_debug("expected non-NULL addresses for 'name' and 'identifiers', exit");
        logger_tracef("free arg(%p) and return with code 1", arg);
        return 1;
    }

    arg->name = name;
    arg->identifiers = identifiers;
    arg->n_identifiers = n_identifiers;

    logger_info("push arg into parser flag_args array");
    Parser *parser_imp = (Parser*)parser;
    int i = push(arg, (void ***)&parser_imp -> flag_args, &parser_imp -> flag_args_count);

    if (i != 0) {
        logger_error("push failed");
        logger_tracef("free arg(%p) and return with code 1", arg);
        free(arg);
        return 1;
    }

    logger_trace("return with code 0");
    return 0;
}

int parser_add_group(parser_t *parser, const char *name, 
                     const char **identifiers, int n_identifiers,
                     unsigned int nargs, const char **default_values) {
    logger_tracef("enter parser_add_group with parameters:\n"
            "- parser = %p\n- name = %p\n- identifiers = %p\n- n_identifiers = %d\n"
            "- nargs = %u\n- default_values = %p", 
            parser, name, identifiers, n_identifiers, nargs, default_values);

    arg_group *arg = (arg_group*)malloc(sizeof(arg_group));
    logger_debugf("memory allocation with size %d(of arg_group) and assign to variable 'arg' at address %p", 
            sizeof(arg_group), arg);
    if (!arg) {
        logger_error("memory allocation failed");
        logger_trace("return with code 1");
        return 1;
    }

    if (!name || !identifiers) {
        free(arg);
        logger_debug("expected non-NULL addresses for 'name' and 'identifiers', exit");
        logger_tracef("free arg(%p) and return with code 1", arg);
        return 1;
    }

    arg->name = name;
    arg->identifiers = identifiers;
    arg->n_identifiers = n_identifiers;
    arg->nargs = nargs;
    arg->default_values = default_values;

    logger_info("push arg into parser group_args array");
    Parser *parser_imp = (Parser*)parser;
    int i = push(arg, (void ***)&parser_imp -> group_args, &parser_imp -> group_args_count);

    if (i != 0) {
        logger_error("push failed");
        logger_tracef("free arg(%p) and return with code 1", arg);
        free(arg);
        return 1;
    }

    logger_trace("return with code 0");
    return 0;
}
