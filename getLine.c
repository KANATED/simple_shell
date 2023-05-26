#include "shell.h"

/**
 * input_buf - afunction to buffers chained commands
 * @info: parameter structure of the function
 * @buf: address of buffer function of a program
 * @len: address of lenght of the function
 *
 * Return: bytes read of the function inserted
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t n = 0;
	size_t len_l = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		n = getline(buf, &len_l, stdin);
#else
		n = _getline(info, buf, &len_l);
#endif
		if (n > 0)
		{
			if ((*buf)[n - 1] == '\n')
			{
				(*buf)[n - 1] = '\0';
				n--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = n;
				info->cmd_buf = buf;
			}
		}
	}
	return (n);
}

/**
 * get_input - Afunction that gets a line minus the newline
 * @info: parameter structure of the function to hold argumenst
 *
 * Return: bytes read func returned
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t v, k, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *b;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		k = v;
		b = buf + k;

		check_chain(info, buf, &k, v, len);
		while (k < len)
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		v = k + 1;
		if (v >= len)
		{
			v = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = b;
		return (_strlen(b));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - acommand line to reads a buffer
 * @info: parameter structure of the function to insert
 * @buf: buffer structure of the function
 * @i: size of the function inserted
 *
 * Return: r in the main
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - Acommand line of the gets next line of input from STDIN
 * @info: parameter structure of the function
 * @ptr: address of pointer to buf used
 * @length: size of preallocated function inserted
 *
 * Return: s on success
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t v, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (v == len)
		v = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + v, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + v, k - v);
	else
		_strncpy(new_p, buf + v, k - v + 1);

	s += k - v;
	v = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Afunction to insert blocks ctrl-C
 * @sig_num: the signal number inputed
 *
 * Return: void as return
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
