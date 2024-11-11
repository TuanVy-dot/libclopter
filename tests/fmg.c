#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <mylib/clopter/1.0.0/clopter.h>

/* I forgot to free memory sadly but it just a test :) */

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        fprintf(stdout, "Usage: %s [command] [filenames]", argv[0]);
        return 1;
    }
    parser_t *CreateParser = parser_create();
    if (!CreateParser) {
        perror("Error: ");
        return 1;
    }
    parser_t *RemoveParser = parser_create();
    if (!RemoveParser) {
        perror("Error: ");
        return 1;
    }
    Args *args;
    const char *command = argv[1];
    const char *fname;
    if (strcmp(command, "create") == 0) {
        args = parser_parse_args(CreateParser, argc, &argv[1]);
        if (!args) {
            perror("Error: ");
            return 1;
        }
        int fnum = args -> remain;
        const char **fnames = args -> leftovers;
        for (int i = 0; i < fnum; i++) {
            fname = fnames[i];
            FILE *file = fopen(fname, "w");
            if (!file) {
                perror("Error: ");
                return 1;
            }
            fclose(file);
        }
        return 0;
    }
    if (strcmp(command, "remove") == 0) {
        args = parser_parse_args(RemoveParser, argc, &argv[1]);
        if (!args) {
            perror("Error: ");
            return 1;
        }
        int fnum = args -> remain;
        const char **fnames = args -> leftovers;
        for (int i = 0; i < fnum; i++) {
            fname = fnames[i];
            if (remove(fname) != 0) {
                perror("Error: ");
                return 1;
            }
        }
        return 0;
    }
    fprintf(stderr, "Error: unknown command %s\n", argv[1]);
    return 0;
}
