#include "shell.h"

/**
 * list_len - A program to determines length of linked list
 * @h: pointer to first node of the program
 *
 * Return: size of list inserted
 */
size_t list_len(const list_t *h)
{
	size_t v = 0;

	while (h)
	{
		h = h->next;
		v++;
	}
	return (v);
}

/**
 * list_to_strings - A program to returns an
 * array of strings of the list->str
 * @head: pointer to first node to insert
 * Return: array of strings to be returned
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), c;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (c = 0; c < a; c++)
				free(strs[c]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - A command line that prints all
 * elements of a list_t linked list
 * @h: pointer to first node to be inserted or inputed
 *
 * Return: size of list used by a program
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - A program to returns node
 * whose string starts with prefix func
 * @node: pointer to list header func next to node
 * @prefix: string to match with the prifix inputed
 * @c: the next character after prefix to match with
 * new one
 *
 * Return: match node or null, if the program compile
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *v = NULL;

	while (node)
	{
		v = starts_with(node->str, prefix);
		if (v && ((c == -1) || (*v == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - a program to gets the index of a node of the func
 * @head: pointer to list head prototype inputed
 * @node: pointer to the node of the header inserted
 *
 * Return: index of node or -1 on the running of the pro
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
