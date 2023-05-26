#include "shell.h"

/**
 * _strlen - afunction that returns the length of a string
 * @s: the string whose length to checked by user
 *
 * Return: integer length of string as result
 */
int _strlen(char *s)
{
	int t = 0;

	if (!s)
		return (0);

	while (*s++)
		t++;
	return (t);
}

/**
 * _strcmp - a program given to performs lexicogarphic
 * comparison of two strangs.
 * @s1: the first strang inputed
 * @s2: the second strang isnerted
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - aprogram to checks if needle starts
 * with haystack
 * and checks it by user command
 * @haystack: string to search for the coma
 * @needle: the substring to find where to start
 *
 * Return: address of next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - aprogram to concatenates two string by user input
 * @dest: the destination buffer of the poitered string
 * @src: the source buffer of the program
 *
 * Return: pointer to destination buffer of the program
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
