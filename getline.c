#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n) {
    static char buffer[BUFFER_SIZE];
    static size_t buffer_index = 0;
    static ssize_t buffer_size = 0;
    ssize_t chars_read = 0;

    if (*n == 0 || *lineptr == NULL) {
        return -1;
    }

    *lineptr = realloc(*lineptr, *n);

    while (1) {
        if ((size_t)buffer_index >= (size_t)buffer_size) {
            buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);

            if (buffer_size <= 0) {
                if (chars_read == 0) {
                    return -1;
                }
                break;
            }

            buffer_index = 0;
        }

        while ((size_t)buffer_index < (size_t)buffer_size) {
            (*lineptr)[chars_read] = buffer[buffer_index];

            if (buffer[buffer_index] == '\n') {
                chars_read++;
                buffer_index++;
                break;
            }

            chars_read++;
            buffer_index++;

            if ((size_t)chars_read >= *n) {
                *n *= 2;
                *lineptr = realloc(*lineptr, *n);
            }
        }

        if ((size_t)buffer_index >= (size_t)buffer_size) {
            break;
        }
    }

    return chars_read;
}
