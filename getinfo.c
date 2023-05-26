#include "shell.h"

/**
 * clear_info - Afunction to initializes info_t struct
 * @info: struct address of an arguments used to
 * keep function prototype cons
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - AFuction to initializes info_t struct
 * @info: struct address of the arguments to store function
 * prototype cons
 * @av: argument vector of the program
 */
void set_info(info_t *info, char **av)
{
	int t = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (t = 0; info->argv && info->argv[t]; t++)
		info->argc = t;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - a command line to frees info_t struct fields
 * @info: struct address of the argumenst used tom keep func pro
 * cons
 * @all: true if freeing all the files info
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
