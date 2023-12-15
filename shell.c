#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Executes a command in a child process and waits for it to complete in the parent.
 * @command: The command to be executed.
 */
void execute_command(char *command) {
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        /* Child process */
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        /* Forking error */
        perror("Error forking");
    } else {
        /* Parent process */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

/**
 * main - The entry point of the simple shell program.
 * Return: Always 0.
 */
int main(void) {
    char *input = NULL;
    size_t len = 0;

    while (1) {
        /* Print the shell prompt */
        printf("#cisfun$ ");

        /* Read user input */
        if (getline(&input, &len, stdin) == -1) {
            if (feof(stdin)) {
                printf("\n");
                free(input);
                exit(EXIT_SUCCESS); /* Handle end of file (Ctrl+D) */
            } else {
                perror("Error reading input");
                exit(EXIT_FAILURE);
            }
        }

        /* Remove newline character from input */
        input[strcspn(input, "\n")] = '\0';

        /* Check for exit command */
        if (strcmp(input, "exit") == 0) {
            free(input);
            exit(EXIT_SUCCESS);
        }

        /* Execute the command */
        execute_command(input);
    }

    return 0;
}
