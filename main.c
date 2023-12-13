#include <stdio.h>
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
 * main - Entry point
 * Return: Always 0
 */
int main(void)
{
	char input[1024];
	char *program_name = "hsh"; /* Change this to match your program name */
	char current_directory[1024];
	size_t len;

	getcwd(current_directory, sizeof(current_directory));

	/* Set up Ctrl+C handler */
	signal(SIGINT, sigint_handler);

	while (1)
	{
		printf("%s$ ", current_directory);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			perror("fgets");
			continue;
		}

		/* Remove the newline character */
		len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}

		/* Handle commands */
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
				display_error(program_name, "cd: No such file or directory");
			}
		}
		else
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				/* Child process */
				char *args[32];
				char *token = strtok(input, " ");
				int arg_count = 0;

				while (token != NULL)
				{
					args[arg_count] = token;
					arg_count++;
					token = strtok(NULL, " ");
				}
				args[arg_count] = NULL;

				/* Execute using PATH or absolute path */
				execvp(args[0], args);
				display_error(program_name, "exec: Command not found");
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				/* Parent process */
				int status;
				waitpid(pid, &status, 0);
			}
			else
			{
				perror("fork");
			}
		}
	}
	return (0);
}
