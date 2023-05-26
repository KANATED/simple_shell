#include "shell.h"

/**
 * is_cmd - aprogram to determines if a file
 * is an executable command
 * @info: info structure of the func to hold potential
 * atguments at cons
 * @path: path to file yused by user
 *
 * Return: 1 if true, 0 otherwise no
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Afunction to duplicates char in program
 * @pathstr: the PATH string of the func
 * @start: starting index of the prog
 * @stop: stopping index of the prog
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buffer[b++] = pathstr[a];
	buffer[b] = 0;
	return (buffer);
}

/**
 * find_path - a function to find this cmd in the PATH string
 * used
 * @info: the info structure of the potential argumnets used to
 * hold func prototype cons
 * @pathstr: the PATH string of the user comand
 * @cmd: the cmd to find the way to path throuth
 *
 * Return: full path of cmd if found or NULL on an error
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
