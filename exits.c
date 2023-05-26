#include "shell.h"

/**
 * _strncpy - acommamd line given to copies string
 * @dest: the destination string copied to be adrresed in
 * @src:  source string of the program
 * @n: amount of characters to be copied or inserted
 * Return: concatenated string to be returned
 */
char *_strncpy(char *dest, char *src, int n)
{
	int v, w;
	char *d = dest;

	v = 0;
	while (src[v] != '\0' && v < n - 1)
	{
		dest[v] = src[v];
		v++;
	}
	if (v < n)
	{
		w = v;
		while (w < n)
		{
			dest[w] = '\0';
			w++;
		}
	}
	return (d);
}

/**
 * _strncat - a function to concatenates two strings
 * @dest: the first string inputed
 * @src: the second string to be inserted
 * @n: the amount of bytes to be maximized
 * Return: concatenated string to be returned
 */
char *_strncat(char *dest, char *src, int n)
{
	int g, v;
	char *d = dest;

	g = 0;
	v = 0;
	while (dest[g] != '\0')
		g++;
	while (src[v] != '\0' && v < n)
	{
		dest[g] = src[v];
		g++;
		v++;
	}
	if (v < n)
		dest[g] = '\0';
	return (d);
}

/**
 * _strchr - Acommand line to locates a character in a string
 * @s: string to be parsed through the program
 * @c: character to look for concatenation
 * Return: (s) pointer to the memory area s in memory adress
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
