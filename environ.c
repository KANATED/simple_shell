#include "shell.h"

/**
 * _myenv - afunction prototype of current environment
 * @info: a structure that hold potential arg. Used to keep
 *          constant func prototype.
 * Return:  0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 *  _getenv - a command line given the value of an environ variable
 * @info: Structureholding potential args
 * @name: env var name of the environ
 *
 * Return: value to be returned
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *v;

	while (node)
	{
		v = starts_with(node->str, name);
		if (v && *v)
			return (v);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - func that Initialize new environment variable
 * to be used
 * @info: Struct holding potential arguments. Used to keep
 *        constant function prototype.
 *  Return: 0 on success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a command linegiven to
 * func Remove environment variable
 * @info: a structure holding potential arguments. Used to keep
 *         func prototype.
 * Return:  0 always
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}
/**
 * populate_env_list - a command line func populates env linked list
 * @info: Structure contain potential arguments. Used to keep
 *           func prototype.
 * Return: always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
