#include "common_functions.h"
#include "parser.h"
#include "executor.h"

/**
 * main - Entry point of the simple shell program.
 * Return: Always 0.
 */
int main(void) {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        /* Print the shell prompt */
        print_prompt();

        /* Read user input */
        if (getline(&input, &len, stdin) == -1) {
            handle_eof(input);
        }

        /* Remove newline character from input */
        input[strcspn(input, "\n")] = '\0';

        /* Check for exit command */
        if (is_exit_command(input)) {
            free(input);
            exit(EXIT_SUCCESS);
        }

        /* Parse and execute the command */
        char **args = parse_input(input);
        execute_command(args);

        /* Free allocated memory */
        free(input);
        free(args);
    }

    return 0;
}
