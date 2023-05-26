#include "shell.h"

/**
 * _strcpy - A program to copies a string
 * @dest: the destination of the poinetr
 * @src: the source code of the user
 *
 * Return: pointer to destination of the user pro
 */
char *_strcpy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * _strdup - A function to duplicates a string
 * @str: the string to duplicate inserted by user
 *
 * Return: pointer to the duplicated string
 * to be returned
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * _puts - acommand given to prints an input string
 * @str: the string to be printed by the user
 *
 * Return: Nothing returend by user
 */
void _puts(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_putchar(str[t]);
		t++;
	}
}

/**
 * _putchar - a program to writes the character c to stdout
 * @c: The character to print what inserted
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set collectly
 */
int _putchar(char c)
{
	static int t;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, buffer, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buffer[t++] = c;
	return (1);
}
