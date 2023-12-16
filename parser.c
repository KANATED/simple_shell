#include "common_functions.h"

/**
 * parse_input - Parses the input into an array of tokens.
 * @input: The input string to parse.
 * Return: An array of tokens.
 */
char **parse_input(char *input) {
    char **tokens;
    char *token;
    char *temp_input;  /* Declare temp_input at the beginning */
    char *temp_token;  /* Declare temp_token at the beginning */

    int token_count = 0;  /* Initialize token_count here */
    int i;  /* Declare i at the beginning */

    if (input == NULL) {
        return NULL;
    }

    /* Count the number of tokens (excluding comments) */
    temp_input = strdup(input);  /* Move the declaration to here */
    if (temp_input == NULL) {
        perror("strdup");
        exit_with_status(1);
    }

    temp_token = strtok(temp_input, " \t\n");  /* Move the declaration to here */
    while (temp_token != NULL) {
        if (temp_token[0] == '#') {
            break;  /* Ignore everything after # */
        }
        token_count++;
        temp_token = strtok(NULL, " \t\n");
    }
    free(temp_input);

    tokens = malloc((token_count + 1) * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc");
        exit_with_status(1);
    }

    for (i = 0, token = strtok(input, " \t\n"); i < token_count; i++, token = strtok(NULL, " \t\n")) {
        if (token[0] == '#') {
            break;  /* Ignore everything after # */
        }
        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            perror("strdup");
            exit_with_status(1);
        }
    }

    tokens[token_count] = NULL;

    return tokens;
}
