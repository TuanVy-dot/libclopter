#include "../api/clopter.h"
#include <stdio.h>
#include <string.h>

/* This is also AI generated */
/* Example about creating subcommands */

// Function prototypes for subcommands
int handle_init(int argc, const char *argv[]);
int handle_remote(int argc, const char *argv[]);
int handle_push(int argc, const char *argv[]);

void print_usage(const char *prog_name) {
    printf("Usage: %s <command> [options]\n\n", prog_name);
    printf("Commands:\n");
    printf("  init     Initialize a new repository\n");
    printf("  remote   Manage remote repositories\n");
    printf("  push     Push changes to remote repository\n");
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *command = argv[1];
    
    // Shift argc and argv to exclude program name and command
    argc -= 1;
    argv += 1;

    if (strcmp(command, "init") == 0) {
        return handle_init(argc, argv);
    } else if (strcmp(command, "remote") == 0) {
        return handle_remote(argc, argv);
    } else if (strcmp(command, "push") == 0) {
        return handle_push(argc, argv);
    } else {
        printf("Unknown command: %s\n", command);
        print_usage(argv[0]);
        return 1;
    }
}

// Initialize command handler
int handle_init(int argc, const char *argv[]) {
    parser_t *parser = parser_create();
    
    // Add --quiet flag
    const char *quiet_ids[] = {"-q", "--quiet"};
    parser_add_flag(parser, "quiet", quiet_ids, 2);
    
    // Add --template option with argument
    const char *template_ids[] = {"-t", "--template"};
    const char *template_defaults[] = {"default"};
    parser_add_group(parser, "template", template_ids, 2, 1, template_defaults);

    Args *args = parser_parse_args(parser, argc, argv);
    
    if (args->remain > 0) {
        printf("Unknown option for init: %s\n", args->leftovers[0]);
        parser_destroy(parser);
        args_destroy(args);
        return 1;
    }

    _Bool quiet = args_get_flag(args, "quiet");
    const char **template = args_get_group(args, "template");

    if (!quiet) {
        printf("Initializing repository with template: %s\n", template[1]);
    }

    parser_destroy(parser);
    args_destroy(args);
    return 0;
}

// Remote command handler
int handle_remote(int argc, const char *argv[]) {
    parser_t *parser = parser_create();
    
    // Add subcommand as positional
    parser_add_positional(parser, "action");
    // Add remote name as positional
    parser_add_positional(parser, "name");
    
    // Add --url option for 'add' action
    const char *url_ids[] = {"-u", "--url"};
    parser_add_group(parser, "url", url_ids, 2, 1, NULL);

    Args *args = parser_parse_args(parser, argc, argv);

    const char *action = args_get_positional(args, "action");
    const char *name = args_get_positional(args, "name");
    const char **url = args_get_group(args, "url");

    if (!action) {
        printf("Missing remote action (add/remove)\n");
        parser_destroy(parser);
        args_destroy(args);
        return 1;
    }

    if (strcmp(action, "add") == 0) {
        if (!name || !url) {
            printf("Remote add requires name and URL\n");
            parser_destroy(parser);
            args_destroy(args);
            return 1;
        }
        printf("Adding remote '%s' with URL: %s\n", name, url[1]);
    } else if (strcmp(action, "remove") == 0) {
        if (!name) {
            printf("Remote remove requires name\n");
            parser_destroy(parser);
            args_destroy(args);
            return 1;
        }
        printf("Removing remote '%s'\n", name);
    } else {
        printf("Unknown remote action: %s\n", action);
        parser_destroy(parser);
        args_destroy(args);
        return 1;
    }

    parser_destroy(parser);
    args_destroy(args);
    return 0;
}

// Push command handler
int handle_push(int argc, const char *argv[]) {
    parser_t *parser = parser_create();
    
    // Add remote name as optional positional
    parser_add_positional(parser, "remote");
    // Add branch name as optional positional
    parser_add_positional(parser, "branch");
    
    // Add --force flag
    const char *force_ids[] = {"-f", "--force"};
    parser_add_flag(parser, "force", force_ids, 2);
    
    // Add --tags flag
    const char *tags_ids[] = {"--tags"};
    parser_add_flag(parser, "tags", tags_ids, 1);
    
    // Add --set-upstream flag with branch name
    const char *upstream_ids[] = {"-u", "--set-upstream"};
    parser_add_flag(parser, "set_upstream", upstream_ids, 2);

    Args *args = parser_parse_args(parser, argc, argv);

    const char *remote = args_get_positional(args, "remote");
    const char *branch = args_get_positional(args, "branch");
    _Bool force = args_get_flag(args, "force");
    _Bool tags = args_get_flag(args, "tags");
    _Bool set_upstream = args_get_flag(args, "set_upstream");

    printf("Pushing to remote '%s' branch '%s'\n", 
           remote ? remote : "origin", 
           branch ? branch : "current");
    
    if (force) printf("Force push enabled\n");
    if (tags) printf("Pushing tags\n");
    if (set_upstream) printf("Setting upstream tracking\n");

    parser_destroy(parser);
    args_destroy(args);
    return 0;
}
