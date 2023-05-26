#include "shell.h"

/**
 * _memset - a command line given by user
 * to fills memory with a constant byte
 * @s: pointer to the memory area or adress of the program
 * @b: byte to fill *s with the memory adress
 * @n: amount of bytes to be filled by user in the progarma
 * Return: (s) a pointer to the memory area s used
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n; t++)
		s[t] = b;
	return (s);
}

/**
 * ffree - acommand line given to frees a string of strings
 * @pp: string of strings to be inseted by user
 */
void ffree(char **pp)
{
	char **c = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(c);
}

/**
 * _realloc - command line given to reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block of the user
 * @old_size: byte size of previous block inserted by user
 * @new_size: byte size of new block to be used by user
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
