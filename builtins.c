#include "common_functions.h"

int is_builtin(char *command) {
    return strcmp(command, "exit") == 0 ||
           strcmp(command, "setenv") == 0 ||
           strcmp(command, "unsetenv") == 0 ||
           strcmp(command, "cd") == 0;
}

void execute_builtin(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit_shell();
    } else if (strcmp(command, "setenv") == 0) {
        execute_setenv();
    } else if (strcmp(command, "unsetenv") == 0) {
        execute_unsetenv();
    } else if (strcmp(command, "cd") == 0) {
        execute_cd();
    }
}

void execute_setenv(void) {
    char **args = parse_input(NULL);

    if (args[1] != NULL && args[2] != NULL && args[3] == NULL) {
        if (setenv(args[1], args[2], 1) == -1) {
            fprintf(stderr, "setenv: Unable to set environment variable\n");
        }
    } else {
        fprintf(stderr, "setenv: Incorrect syntax\n");
    }

    free(args);
}

void execute_unsetenv(void) {
    char **args = parse_input(NULL);

    if (args[1] != NULL && args[2] == NULL) {
        if (unsetenv(args[1]) == -1) {
            fprintf(stderr, "unsetenv: Unable to unset environment variable\n");
        }
    } else {
        fprintf(stderr, "unsetenv: Incorrect syntax\n");
    }

    free(args);
}

void execute_cd(void) {
    char **args = parse_input(NULL);

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        args[1] = getenv("HOME");
    }

    if (strcmp(args[1], "-") == 0) {
        char *old_pwd = getenv("OLDPWD");
        if (old_pwd == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return;
        }
        args[1] = old_pwd;
    }

    if (chdir(args[1]) == -1) {
        perror("cd");
    } else {
        char *cwd = getcwd(NULL, 0);
        if (cwd != NULL) {
            setenv("PWD", cwd, 1);
            free(cwd);
        } else {
            perror("getcwd");
        }
    }

    free(args);
}
