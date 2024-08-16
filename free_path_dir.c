#include "simple_shell.h"

/**
 * free_path_dir - frees a singly linked list
 * @head: is the first element of the list
 *
 * Return: Always nothing
 */
void free_path_dir(dir_t *head)
{
	dir_t *curr_node = NULL;

	while (head != NULL)
	{
		curr_node = head;	/* Stores the current node */
		head = head->next;	/* Move head to the next node */

		/* Free the elements of the node and assign it the value NULL */
		free(curr_node->name);
		curr_node->name = NULL;

		free(curr_node->path);
		curr_node->path = NULL;

		free(curr_node);	/* Free the node */
		curr_node = NULL;
	}
}
