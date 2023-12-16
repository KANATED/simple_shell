#include "common_functions.h"

/* common_functions.c
 *
 * Implementation of common functions used in the shell.
 */

#include "common_functions.h"

/**
 * exit_shell - Exits the shell.
 */
void exit_shell(void)
{
    /* Implementation of exit_shell */
    /* For example: */
    printf("Exiting the shell.\n");
    exit(0);
}

/**
 * exit_with_status - Exits the shell with a specific status code.
 * @status: The exit status code.
 */
void exit_with_status(int status)
{
    /* Implementation of exit_with_status */
    /* For example: */
    printf("Exiting the shell with status: %d\n", status);
    exit(status);
}

/**
 * free_resources - Frees any allocated resources used by the shell.
 */
void free_resources(void)
{
    /* Implementation of free_resources */
    /* For example: */
    printf("Freeing allocated resources.\n");
    /* free any dynamically allocated resources here */
}
