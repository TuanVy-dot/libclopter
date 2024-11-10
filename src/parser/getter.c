#include "getter.h" /* already include parser_n_arg and parsing header */
#include "log_api.h"

int parser_search_positional(parser_t *parser, const char *name) {
    logger_tracef("enter parser_search_positional with parameters:\n"
            "- parser = %p\n- name = %p", parser, name);

    Parser *parser_imp = (Parser*)parser;
    arg_positional **curr = parser_imp -> positional_args;
    int len = parser_imp -> positional_args_count;

    if (!curr || len <= 0) {
        logger_trace("return with code -1");
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (strcmp((*curr) -> name, name) == 0) {
            logger_tracef("return with index %d", i);
            logger_infof("found positional at %d", i);
            return i;
        } 
        curr++;
    }

    logger_trace("return with code -1");
    logger_info("positional not found");
    return -1;
}

int parser_search_flag(parser_t *parser, const char *name) {
    logger_tracef("enter parser_search_flag with parameters:\n"
            "- parser = %p\n- name = %p", parser, name);

    Parser *parser_imp = (Parser*)parser;
    arg_flag **curr = parser_imp -> flag_args;
    logger_tracef("address of curr: %p", curr);
    int len = parser_imp -> flag_args_count;

    if (!curr || len <= 0) {
        logger_trace("return with code -1");
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (strcmp((*curr) -> name, name) == 0) {
            logger_tracef("return with index %d", i);
            logger_infof("found flag at %d", i);
            return i;
        } 
        curr++;
    }

    logger_trace("return with code -1");
    logger_info("flag not found");
    return -1;
}

int parser_search_group(parser_t *parser, const char *name) {
    logger_tracef("enter parser_search_group with parameters:\n"
            "- parser = %p\n- name = %p", parser, name);

    Parser *parser_imp = (Parser*)parser;
    arg_group **curr = parser_imp -> group_args;
    int len = parser_imp -> group_args_count;

    if (!curr || len <= 0) {
        logger_trace("return with code -1");
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (strcmp((*curr) -> name, name) == 0) {
            logger_tracef("return with index %d", i);
            logger_infof("group found at %d", i);
            return i;
        } 
        curr++;
    }

    logger_trace("return with code -1");
    logger_info("group not found");
    return -1;
}

const char *args_get_positional(Args *args, char *name) {
    Parser *parser = (Parser *)args -> Parser;
    int index = parser_search_positional((parser_t *)parser, name);
    if (index < 0) {
        return NULL;
    }
    return (args -> positional)[index];
}

_Bool args_get_flag(Args *args, char *name) {
    Parser *parser = (Parser *)args -> Parser;
    int index = parser_search_flag((parser_t *)parser, name);
    if (index < 0) {
        return NULL;
    }
    return (args -> flags)[index];
}

const char **args_get_group(Args *args, char *name) {
    Parser *parser = (Parser *)args -> Parser;
    int index = parser_search_group((parser_t *)parser, name);
    if (index < 0) {
        return NULL;
    }
    return (args -> groups)[index];
}
