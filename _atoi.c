#include "shell.h"

/**
 * interactive - A func that return true if
 * shell is interactive mode that we need
 * @info: struct addressto input into theprogram
 * Return: 1 if interactive mode, 0 otherwise or an error
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - a funciton to checks if char is a delimeter
 * or not
 * @c: the char to be inserted
 * @delim: delimeter string inputed in a progr
 * Return: 1 on success, 0 if fails
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - A function to checks for alphabetic
 * char inputed in aprogram
 * @c: The character to input in a program
 * Return: 1 if c is an alphabet, 0 otherwise or if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - A function to converts string to integer
 * we have inserted in aprogram
 * @s: converted string to integer
 * Return: 0 if no numbers in string, otherwise
 *
 */

int _atoi(char *s)
{
	int t, sign = 1, flag = 0, write;
	unsigned int res = 0;

	for (t = 0; s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sign *= -1;

		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		write = -res;
	else
		write = res;

	return (write);
}
