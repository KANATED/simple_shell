#include "common_functions.h"

/**
 * parse_input - Parses the input into an array of tokens.
 * @input: The input string to parse.
 * Return: An array of tokens.
 */
char **parse_input(char *input) {
    char **tokens;
    char *token;
    int token_count = 0;

    if (input == NULL) {
        return NULL;
    }

    /* Count the number of tokens (excluding comments) */
    char *temp_input = strdup(input);
    char *temp_token = strtok(temp_input, " \t\n");
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

    token = strtok(input, " \t\n");
    for (int i = 0; i < token_count; i++) {
        if (token[0] == '#') {
            break;  /* Ignore everything after # */
        }
        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            perror("strdup");
            exit_with_status(1);
        }
        token = strtok(NULL, " \t\n");
    }

    tokens[token_count] = NULL;

    return tokens;
}
