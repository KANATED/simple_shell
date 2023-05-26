#include "shell.h"

/**
 * bfree - a program to frees a pointer and NULLs the address
 * of the user
 * @ptr: address of the pointer to free by user comand
 *
 * Return: 1 if freed, otherwise 0on an error
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
