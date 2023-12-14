#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

#define MAX_ARGS 32

void display_error(const char *program, const char *message);
void sigint_handler(int signum);
int execute_shell(void);

#endif /* SHELL_H */
