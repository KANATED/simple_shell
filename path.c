#include "common_functions.h"

/**
 * find_full_path - Finds the full path of a command.
 * @command: The command to find the path for.
 * Return: The full path of the command, or NULL if not found.
 */
char *find_full_path(char *command) {
    char *path;
    char *full_path;
    char **directories;
    int i;

    if (command == NULL) {
        return NULL;
    }

    path = getenv("PATH");
    if (path == NULL) {
        return NULL;
    }

    directories = parse_input(path);

    for (i = 0; directories[i] != NULL; i++) {
        full_path = malloc(strlen(directories[i]) + strlen(command) + 2);
        if (full_path == NULL) {
            perror("malloc");
            exit_with_status(1);
        }
        sprintf(full_path, "%s/%s", directories[i], command);
        if (access(full_path, F_OK) == 0) {
            free(directories);
            return full_path;
        }
        free(full_path);
    }

    free(directories);
    return NULL;
}
