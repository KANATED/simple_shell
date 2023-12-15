#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * display_error - Display error messages with program name
 * @program: Program name
 * @message: Error message
 */
void display_error(const char *program, const char *message)
{
    fprintf(stderr, "%s: %s\n", program, message);
}

/**
 * sigint_handler - Handle Ctrl+C signal
 * @signum: Signal number
 */
void sigint_handler(int signum)
{
    (void)signum;
    printf("\n");
}

/**
 * execute_shell - Main function to execute the shell
 * Return: Always 0
 */
int execute_shell(void)
{
    char input[1024];
    char *program_name = "hsh"; /* Change this to match your program name */
    char current_directory[1024];
    size_t len;

    getcwd(current_directory, sizeof(current_directory));

    signal(SIGINT, sigint_handler);

    while (1)
    {
        printf("%s$ ", current_directory);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            perror("fgets");
            continue;
        }

        len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }
        else
        {
            display_error(program_name, "Input too long");
            continue;
        }

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        else if (strncmp(input, "cd ", 3) == 0)
        {
            char *directory = input + 3;
            if (chdir(directory) == 0)
            {
                getcwd(current_directory, sizeof(current_directory));
            }
            else
            {
                perror("chdir");
                display_error(program_name, "cd: No such file or directory");
            }
        }
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                char *args[MAX_ARGS];
                char *token = strtok(input, " ");
                int arg_count = 0;

                while (token != NULL)
                {
                    args[arg_count] = token;
                    arg_count++;
                    token = strtok(NULL, " ");
                }
                args[arg_count] = NULL;

                execvp(args[0], args);
                perror("execvp");
                display_error(program_name, "exec: Command not found");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                int status;
                if (waitpid(pid, &status, 0) == -1)
                {
                    perror("waitpid");
                    /* Handle error */
                }
            }
            else
            {
                perror("fork");
            }
        }
    }

    return 0;
}
