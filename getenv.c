#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 32

/* display_error - Display error messages with program name
 * @program: Program name
 * @message: Error message
 *
 * Description: This function prints error messages to stderr with the
 * program name and a specified message.
 */
void display_error(const char *program, const char *message)
{
    fprintf(stderr, "%s: %s\n", program, message);
}

/* execute_command - Execute a command in a child process
 * @command: The command to execute
 *
 * Description: This function forks a child process and executes the specified
 * command. If the command is not found, it prints an error message.
 */
void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execvp(command, NULL) == -1)
        {
            perror("execvp");
            display_error(command, "Command not found");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }
}

/* main - Entry point for the simple shell
 * Return: Always 0
 *
 * Description: This function serves as the entry point for the simple shell.
 * It prompts the user for input, checks if the command exists, and executes it
 * in a child process. If the command is not found, it displays an error message.
 */
int main(void)
{
    char input[1024];

    while (1)
    {
        /* Prompt for user input */
        printf("$ ");
        fgets(input, sizeof(input), stdin);

        /* Remove newline character */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }

        /* Check if the command exists before calling fork */
        if (access(input, X_OK) == 0)
        {
            execute_command(input);
        }
        else
        {
            /* Display error for invalid command */
            display_error("shell", "Invalid command");
        }
    }

    return 0;
}
