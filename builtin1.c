#include "shell.h"

/**
 * _myhistory - a command to displays history list, biggining from 0.
 * @info: Structure that holds potential arguments. Used to keep
 *        constant func prototype.
 *  Return: 0 always
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - a acommand given to sets alias to string
 * @info: parameter structure inputed
 * @str: string alias inserted
 *
 * Return: 0 on success, 1 on fail or eerno
 */
int unset_alias(info_t *info, char *str)
{
	char *t, v;
	int w;

	t = _strchr(str, '=');
	if (!t)
		return (1);
	v = *t;
	*t = 0;
	w = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*t = v;
	return (w);
}

/**
 * set_alias - a command line given to sets alias to string
 * @info: parameter structure to be inserted
 * @str: string alias of a program
 *
 * Return: 0 on success, 1 on error or on fail
 */
int set_alias(info_t *info, char *str)
{
	char *t;

	t = _strchr(str, '=');
	if (!t)
		return (1);
	if (!*++t)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - A command line given to prints an alias string
 * @node: the alias node of the program
 *
 * Return: Always 0 on success, 1 on errorno or fails
 */
int print_alias(list_t *node)
{
	char *t = NULL, *v = NULL;

	if (node)
	{
		t = _strchr(node->str, '=');
		for (v = node->str; v <= t; v++)
		_putchar(*v);
		_putchar('\'');
		_puts(t + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - acommand line given to mimics alias builtin (man alias)
 * info: Structure that holspotential arguments. Used to keep
 *          constant func prototype.
 *  Return: 0 always on success
 */
int _myalias(info_t *info)
{
	int t = 0;
	char *v = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		v = _strchr(info->argv[t], '=');
		if (v)
			set_alias(info, info->argv[t]);
		else
			print_alias(node_starts_with(info->alias, info->argv[t], '='));
	}

	return (0);
}
