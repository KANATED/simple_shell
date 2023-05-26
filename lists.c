#include "shell.h"

/**
 * add_node - aprogram that adds a node to the start of the list
 * @head: address of pointer to head node next with
 * @str: str field of node used to inpute
 * @num: node index used by history of the profgram
 *
 * Return: size of list to be returned
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end -A program to adds node to end of the list
 * @head: address of pointer to head node to the end
 * @str: str field of node of the pro inserted
 * @num: node index used by history to list all the func
 *
 * Return: size of list to be returned
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - a commamd line that prints only the string
 * element of  list_t linked list
 * @h: pointer to first node of the func to pint o=to
 * Return: size of list to be returned
 */
size_t print_list_str(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * delete_node_at_index - a funxtion to deletes
 * node at given index
 * @head: address of pointer to first node of the program
 * @index: index of node inputed by the user to delete
 *
 * Return: 1 on success, 0 on failure or on anerror
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - aprogram to frees all nodes of a list
 * inputed by user
 * @head_ptr: address of pointer to head node to the next
 * func user inputed
 * Return: void always on success
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
