#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

/* Function prototypes */

ssize_t my_getline(char **lineptr, size_t *n);
void print_prompt(void);
void handle_eof(char *input);
int is_exit_command(char *input);
char **parse_input(char *input);
char *find_full_path(char *command);
extern int last_status;
void execute_command(char **args);
int is_builtin(char *command);
void execute_builtin(char *command);
void exit_shell(void);
void free_resources(void);
void exit_with_status(int status);
void execute_setenv(void);
void execute_unsetenv(void);
void execute_cd(void);
void execute_alias(char **args);
void print_aliases(void);
void handle_variables(char **args);

#endif /* COMMON_FUNCTIONS_H */
