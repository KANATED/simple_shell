#include "shell.h"

/**
 * get_history_file - Afunction to gets the history file
 * @info: parameter structure of the arguments used
 * to keep func prototype cons
 *
 * Return: allocated string holds history file
 */

char *get_history_file(info_t *info)
{
	char *buffer, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dr);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - acommand line given to creates a file,
 * or appends to an existing file
 * @info: the parameter structure of the function used
 *
 * Return: 1 on success, else -1 on annerrno
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Acommand line that reads history from file
 * @info: the parameter structure of the arguments that hold
 * func prototype cons
 *
 * Return: histcount 0 otherwise no
 */
int read_history(info_t *info)
{
	int j, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_history_list(info, buf + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structurethat holds potential arguments. Used to keep
 * func prototype cons
 * @buf: buffer adress of the func
 * @linecount: the history linecount of the insrted args
 *
 * Return: 0 on sucess
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - acommand line renumbers used to link
 * history after changes
 * you did
 * @info: Structure that holds potential arguments. Used to keep func
 * prototype cons
 * Return: the new histcount to be returned
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int v = 0;

	while (node)
	{
		node->num = v++;
		node = node->next;
	}
	return (info->histcount = v);
}
