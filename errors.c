#include "shell.h"

/**
 * _eputs - acommand line to prints an inputed string
 * @str: string printed to the program
 *
 * Return: Nothing always
 */
void _eputs(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_eputchar(str[t]);
		t++;
	}
}

/**
 * _eputchar - A program to writes char c to stderr
 * @c: character inputed in program
 * Return: On success 1
 * On failer, -1 is returned, and errno is set collectly
 */
int _eputchar(char c)
{
	static int v;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buffer, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buffer[v++] = c;
	return (1);
}

/**
 * _putfd - acommand line that writes character c to fd
 * @c: The character to be printed
 * @fd: filedescriptor to write to the program
 *
 * Return: On success 1.
 * On fails, -1 is returned, and set collectly.
 */
int _putfd(char c, int fd)
{
	static int v;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buffer[v++] = c;
	return (1);
}

/**
 * _putsfd - acomand line to prints inputed string
 * @str: string printed by program
 * @fd: filedescriptor to write to the program
 *
 * Return: the number of chars putted inside of the progfram
 */
int _putsfd(char *str, int fd)
{
	int v = 0;

	if (!str)
		return (0);
	while (*str)
	{
		v += _putfd(*str++, fd);
	}
	return (v);
}
