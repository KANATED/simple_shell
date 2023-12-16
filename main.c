#include "common_functions.h"

/**
 * main - Entry point for the shell.
 * @argc: The number of command line arguments.
 * @argv: An array of command line argument strings.
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv) {
    char *line = NULL;
    size_t len = 0;
    char **commands;
    char **args;

    int i;  /* Declare i outside the for loop */

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        /* Execute commands from file */
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("fopen");
            return 1;
        }

        while ((getline(&line, &len, file)) != -1) {
            commands = parse_input(line);

            for (i = 0; commands[i] != NULL; i++) {
                args = parse_input(commands[i]);
                execute_command(args);
                free(args);
            }

            free(commands);
        }

        fclose(file);
        free(line);
        return 0;
    }

    /* Interactive mode */
    while ((my_getline(&line, &len)) != -1) {
        commands = parse_input(line);

        for (i = 0; commands[i] != NULL; i++) {
            args = parse_input(commands[i]);
            execute_command(args);
            free(args);
        }

        free(commands);
    }

    free_resources();

    return 0;
}
