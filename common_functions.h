#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_prompt(void);
void handle_eof(char *input);
int is_exit_command(char *input);

#endif /* COMMON_FUNCTIONS_H */
