#include "hsh.h"

/**
 * create_node - creat a node at last position in a linked list
 * @head: is the start of a linked list
 * @name: is the name of environment variable
 * @value: is the value of the variable
 *
 * Return: a new node or NULL if fail
 */
dir_t *create_node(dir_t **head, char *name, char *value)
{
	dir_t *new_node = NULL, *curr_node = NULL;

	new_node = malloc(sizeof(dir_t));
	if (new_node == NULL)
	{
		free_path_dir(*head);
		error_handling("malloc", EXIT_FAILURE);
	}

	new_node->name = strdup(name);
	new_node->path = strdup(value);
	if (new_node->name == NULL || new_node->path == NULL)
	{
		free_path_dir(*head);
		error_handling("strdup", EXIT_FAILURE);
	}
	new_node->next = NULL;

	if (*head == NULL)
		*head = new_node;
	else
	{
		curr_node = *head;

		while (curr_node->next != NULL)
			curr_node = curr_node->next;

		curr_node->next = new_node;
	}
	return (new_node);
}
