#include "shell.h"

/**
 * get_environ - afunction to returns string array copy of environ
 * @info: Structure to hold potential arguments. Used keep
 *           func. prototype.
 * Return: 0 always on suces
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Acommand line to Remove an environment variable
 * @info: Astructure to hold potential arguments. Used to keep
 *         func. prototype.
 * Return: 1 on delete, 0
 * @var: the string env var property of the program
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *t;

	if (!node || !var)
		return (0);

	while (node)
	{
		t = starts_with(node->str, var);
		if (t && *t == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), *t);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - a command line to Initializes new environ variable
 * @info: Structure to hold arguments
 * @var: string env var property of the program
 * @value: string env var value of the program
 * Return: always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *b;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
