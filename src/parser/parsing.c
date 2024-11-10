#include "parsing.h"
#include "parser_n_arg.h"
#include "log_api.h"
#include "general.h" /* For macros */
#include <stdlib.h>
#include <stdbool.h>

Args *parser_parse_args(parser_t *parser, int argc, const char *argv[]) {
    logger_tracef("Enter parser_parse_args with parameters:\n"
                          "- parser = %p\n- argc = %d\n- argv = %p",
                          parser, argc, argv);
    logger_info("parsing args");

    Parser *parser_imp = (Parser *)parser;
    int flags_count = parser_imp -> flag_args_count;
    int positional_count = parser_imp -> positional_args_count;
    int groups_count = parser_imp -> group_args_count;

    /* Init all to NULL before use */
    const char **positional_container = NULL;
    bool *flag_container = NULL;
    const char ***group_container = NULL;
    const char **leftovers = NULL;
    Args *containers = NULL;

    positional_container = calloc(positional_count, sizeof(void*));
    if (!positional_container) {
        goto pos_fail;
    }

    flag_container = malloc(flags_count * sizeof(bool));
    if (!flag_container) {
        goto flag_fail;
    }
    
    group_container = malloc(groups_count * sizeof(void*));
    if (!group_container) {
        goto grp_fail;
    }

    containers = malloc(sizeof(Args));
    if (!containers) {
        goto cont_fail;
    }

    /* initualization */
    /* copy argv */
    int argv_size = argc * sizeof(void *);
    char **argv_c = malloc(argv_size);
    if (!argv_c) {
        goto argv_cp_fail;
    }

    memcpy(argv_c, argv, argv_size);
    argv_c[0] = NULL;
    logger_tracef("copy argv %p to argv_c %p", argv, argv_c);

    /* We don't need positional because it don't have identifiers
     * Simply check otbers and take the leftovers */
    arg_flag **flag_args = parser_imp -> flag_args;
    arg_group **group_args = parser_imp -> group_args;
    int temp_top;

    /* Group parsing */
    temp_top = 0;
    for (int i = 0; i < groups_count; i++) {
        bool found = false;
        arg_group *curr_grp = group_args[i];
        const char **identifiers = curr_grp ->  identifiers;
        int n_identifiers = curr_grp -> n_identifiers;
        int nargs = curr_grp -> nargs;
        const char **cont = calloc((nargs + 1), sizeof(void *));

        if (!cont) {
            goto grpcont_fail;
        }
        int l = 0;
        /* Allocate memory enough to store this group, including its identifier */
        for (int j = 0; j < argc; j++) {
            const char *arg = argv_c[j];
            if (!arg) continue;
            for (int k = 0; k < n_identifiers && !found; k++) {
                const char *identifier = identifiers[k];
                if (STREQ(arg, identifier)) {
                    for (; l <= nargs && argv_c[j] && j < argc; l++, j++) {
                        cont[l] = argv_c[j];
                        argv_c[j] = NULL;

                    }
                }
            }
        }
        group_container[temp_top++] = cont;
    }

    temp_top = 0;
    /* Flags parsing */
    logger_info("start to parse flags");
    for (int i = 0; i < flags_count; i++) {
        bool found = false;
        arg_flag *curr_flag = flag_args[i];
        const char **identifiers = curr_flag -> identifiers;
        int n_identifiers = curr_flag -> n_identifiers;
        for (int j = 0; j < argc && !found; j++) {
            const char *arg = argv_c[j];
            if (!arg) continue;
            for (int k = 0; k < n_identifiers; k++) {
                const char *identifier = identifiers[k];
                if (STREQ(arg, identifier)) {
                    argv_c[j] = NULL;
                    found = true;
                    break;
                }
            }
        }
        flag_container[temp_top++] = found;
    }

    temp_top = 0;
{
    int j = 0;
    for (int i = 0; i < positional_count && j < argc; i++) {
        for (; j < argc; j++) {
            if (argv_c[j]) {
                positional_container[temp_top++] = argv_c[j];
                argv_c[j++] = NULL;
                break;
            }
        }
    }
} /* limit the scope of j */

    temp_top = 0;
{
    leftovers = calloc(1, sizeof(void *));
    void *temp;
    int i;
    for (i = 0; i < argc; i++) {
        if (argv_c[i]) {
            temp = realloc(leftovers, (temp_top + 1) * sizeof(void *));
            if (!temp) {
                goto leftovers_realloc_fail;
            }
            leftovers = temp;
            leftovers[temp_top++] = argv_c[i];
        }
    }
    containers -> remain = temp_top;
}
    containers -> Parser = parser;
    containers -> positional = positional_container;
    containers -> flags = flag_container;
    containers -> groups = group_container;
    containers -> leftovers = leftovers;

    free(argv_c);
    return containers;

/* Memory handling, fall through behavior */
leftovers_realloc_fail:
    free(leftovers);
grpcont_fail:
    free(argv_c);
argv_cp_fail:
    free(containers);
cont_fail:
    free(group_container);
grp_fail:
    free(positional_container);
pos_fail:
    free(flag_container);
flag_fail:
    return NULL;
} 

void args_destroy(Args *args) {
    if (args -> positional) {
        free(args -> positional);
    }
    if (args -> flags) {
        free(args -> flags);
    }
    if (args -> groups) {
        free(args -> groups);
    }
    if (args -> leftovers) {
        free(args -> leftovers);
    }
    free(args);
}
