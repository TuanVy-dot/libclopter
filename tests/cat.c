#include "../api/clopter.h"
#include <stdio.h>
#include <errno.h>

int main(int argc, const char *argv[]) {

    int c;
    if (argc < 2) {
        while ((c = getchar()) != EOF) {
            putc(c, stdout);
        }
        return 0;
    }

    parser_t *parser = parser_create();
    Args *args = parser_parse_args(parser, argc, argv);

    const char **filenames = (args -> leftovers);
    int count = args -> remain;

    FILE *file;
    for (int i = 0; i < count; i++) {
        file = fopen(filenames[i], "r");
        if (!file) {
            if (errno == EISDIR) {
                fprintf(stderr, "\ncat: %s: is a directory\n", filenames[i]);
                continue;
            } else if (errno == ENOENT) {
                fprintf(stderr, "\ncat: %s: no such file or directory\n", filenames[i]);
                continue;
            } else {
                fprintf(stderr, "\nCriticalError: allocation failed\n");
                return 1;
            }
        }
        while ((c = getc(file)) != EOF) {
            putc(c, stdout);
        }
        fclose(file);
    }

    return 0;
}
