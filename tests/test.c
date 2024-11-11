#include <stdio.h>
#include <mylib/clopter/1.0.0/clopter.h>

int main(int argc, const char *argv[]) {
    // Create a new parser
    parser_t *parser = parser_create();

    // Add some positional arguments
    parser_add_positional(parser, "input_file");
    parser_add_positional(parser, "output_file");

    // Add a flag argument (e.g., --verbose)
    const char *verbose_flags[] = {"--verbose", "-v"};
    parser_add_flag(parser, "verbose", verbose_flags, 2);

    // Add a group argument (e.g., --operands with two numbers)
    const char *operands_identifiers[] = {"--operands"};
    const char *default_values[] = {"1", "2"};
    parser_add_group(parser, "operands", operands_identifiers, 1, 2, default_values);

    // Parse the arguments
    Args *args = parser_parse_args(parser, argc, argv);

    // Retrieve and print the positional arguments
    const char *input_file = args_get_positional(args, "input_file");
    const char *output_file = args_get_positional(args, "output_file");
    printf("Input File: %s\n", input_file);
    printf("Output File: %s\n", output_file);

    // Check for the verbose flag and print if set
    if (args_get_flag(args, "verbose")) {
        printf("Verbose flag is set\n");
    }

    // Retrieve and print the operands group
    const char **operands = args_get_group(args, "operands");
    printf("Operands: %s, %s\n", operands[1], operands[2]);

    // Clean up
    args_destroy(args);
    parser_destroy(parser);

    return 0;
}
