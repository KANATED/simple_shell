#include "common_functions.h"

extern int last_status;

int last_status = 0;

/**
 * replace_variables - Replaces variables in the command arguments.
 * @args: The command arguments to replace variables in.
 * Return: A new array with variables replaced.
 */
char **replace_variables(char **args) {
    char **new_args;
    int arg_count = 0;
    int i;

    while (args[arg_count] != NULL) {
        arg_count++;
    }

    new_args = malloc((arg_count + 1) * sizeof(char *));
    if (new_args == NULL) {
        perror("malloc");
        exit_with_status(1);
    }

    for (i = 0; i < arg_count; i++) {
        if (strcmp(args[i], "$?") == 0) {
            char status_str[4];  /* Assuming status can be represented in 3 digits */
            sprintf(status_str, "%d", last_status);
            new_args[i] = strdup(status_str);
        } else if (strcmp(args[i], "$$") == 0) {
            char pid_str[16];  /* Assuming pid can be represented in 15 digits */
            sprintf(pid_str, "%d", getpid());
            new_args[i] = strdup(pid_str);
        } else {
            new_args[i] = strdup(args[i]);
        }

        if (new_args[i] == NULL) {
            perror("strdup");
            exit_with_status(1);
        }
    }

    new_args[arg_count] = NULL;

    return new_args;
}

/**
 * execute_command - Executes a command with arguments.
 * @args: The array of command arguments.
 */
void execute_command(char **args) {
    pid_t pid;
    int status;

    args = replace_variables(args);

    if (find_full_path(args[0]) == NULL) {
        if (is_builtin(args[0])) {
            execute_builtin(args[0]);
        } else {
            fprintf(stderr, "Command not found: %s\n", args[0]);
        }
        free(args);
        return;
    }

    pid = fork();

    if (pid == 0) {
        if (execve(args[0], args, environ) == -1) {
            perror("execve");
            exit_with_status(127);
        }
    } else if (pid < 0) {
        perror("fork");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        last_status = WEXITSTATUS(status);
    }

    free(args);
}
