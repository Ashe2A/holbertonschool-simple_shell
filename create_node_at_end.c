#include "simple_shell.h"

/**
 * create_node_at_end - creates a node
 * and appends it to the end of a linked list
 * @head: A pointer to the pointer of the first node in the linked list
 * @name: is a string containing the name of the environment variable
 * @value: is the value of the variable
 *
 * Description: The function creates a new node by allocating memory to it.
 * It copies the values of name and value into its structure.
 * The node is placed at the end of the list. next points to NULL.
 * It returns the new node. If memory allocation fails, NULL is returned.
 *
 * Return: A pointer to the newly created node, or NULL if memory allocation
 * fails
 */
dir_t *create_node_at_end(dir_t **head, char *name, char *value)
{
	dir_t *new_node = NULL, *curr_node = NULL;

	/* Allocate memory ti the new node */
	new_node = malloc(sizeof(dir_t));
	if (new_node == NULL)	/* Malloc check */
	{
		free_path_dir(*head);
		error_handling("malloc", EXIT_FAILURE);
	}

	/* Copy the strings name and value */
	new_node->name = strdup(name);
	new_node->path = strdup(value);
	/* strdup check */
	if (new_node->name == NULL || new_node->path == NULL)
	{
		free_path_dir(*head);
		error_handling("strdup", EXIT_FAILURE);
	}
	/* Set the pointer next to NULL. The node is the last */
	new_node->next = NULL;

	/* If the list does not exist */
	if (*head == NULL)
		*head = new_node;	/* The new node becomes the head */
	else
	{
		/* We use the search node to access the last node */
		curr_node = *head;
		while (curr_node->next != NULL)
			curr_node = curr_node->next;

		/* The new node takes the place of last */
		curr_node->next = new_node;
	}
	return (new_node);
}
