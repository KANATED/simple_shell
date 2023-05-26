#include "shell.h"

/**
 * _erratoi - aommand line to converts a string to an integer
 * @s: string converted into an integer
 * Return: 0 if verted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int j = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			res *= 10;
			res += (s[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - acommand line given to prints error message
 * @info: parameter & return info structure of the given
 * func
 * @estr: string that holds an error type
 * Return: 0 if no numbers inputed in string, converted number otherwise
 *        -1 on error as return
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - acommand line given to prints decimal(integer)
 * @input: insert a number
 * @fd:  filedescriptor of the func to write to
 *
 * Return: number of characters printed to act as return
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - acommand line given to convert function, a clone of itoa
 * @num: number to be converted
 * @base: base of the number inserted
 * @flags: argument flags of the potential structure
 *
 * Return: string to return
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long v = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		v = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[v % base];
		v /= base;
	} while (v != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - acomand line given to replaces first
 * instance of '#' with '\0'
 * @buf: address of buffer string to be modified in a memeory
 *
 * Return: 0 always
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
