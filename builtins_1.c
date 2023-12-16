#include "common_functions.h"

void execute_alias(char **args);
void print_aliases(void);

/**
 * execute_alias - Executes the alias built-in command.
 * @args: The arguments passed to the alias command.
 */
void execute_alias(char **args) {
    if (args[1] == NULL) {
        /* No arguments, print all aliases */
        print_aliases();
    } else {
        /* Define or print specific aliases */
        int i;
        for (i = 1; args[i] != NULL; i++) {
            char *name = strtok(args[i], "=");
            char *value = strtok(NULL, "=");

            if (value != NULL) {
                /* Define alias */
                setenv(name, value, 1);
            } else {
                /* Print alias */
                char *alias_value = getenv(name);
                if (alias_value != NULL) {
                    printf("%s='%s'\n", name, alias_value);
                }
            }
        }
    }

    free(args);
}

/**
 * print_aliases - Prints all aliases.
 */
void print_aliases(void) {
    char **env;
    for (env = environ; *env != NULL; env++) {
        char *name = strtok(*env, "=");
        char *value = strtok(NULL, "=");

        if (name != NULL && value != NULL && name[0] != '\0') {
            printf("%s='%s'\n", name, value);
        }
    }
}
