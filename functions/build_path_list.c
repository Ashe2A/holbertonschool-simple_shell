#include "simple_shell.h"

/**
 * create_node_at_end - appends a node to the end of a linked list
 * @head: linked list
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @user_input: raw user input
 *
 * Description: The function creates a new node by allocating memory to it.
 * It copies the values of name and value into its structure.
 * The node is placed at the end of the list. next points to NULL.
 * It returns the new node. If memory allocation fails, NULL is returned.
 *
 * Return: the newly created node, or NULL if malloc fails
 */
dir_t *create_node_at_end(dir_t **head, char *name, char *value,
				char *user_input)
{
	dir_t *new_node = NULL, *curr_node = NULL;

	/* Allocate memory to the new node */
	new_node = malloc(sizeof(dir_t));
	if (new_node != NULL) /* Malloc check */
	{
		/* Copy the strings name and value */
		new_node->name = strdup(name);
		new_node->path = strdup(value);
		/* strdup check */
		if ((new_node->name != NULL) && (new_node->path != NULL))
		{
			/* Set the pointer next to NULL. The node is the last */
			new_node->next = NULL;

			/* If the list does not exist */
			if (*head != NULL)
			{
				/* We use the search node to access the last node */
				curr_node = *head;
				while (curr_node->next != NULL)
					curr_node = curr_node->next;

				/* The new node takes the place of last */
				curr_node->next = new_node;
			}
			else
				*head = new_node; /* The new node becomes the head */
			return (new_node);	
		}
		free(user_input);
		free_path_dir(*head);
		error_handling("strdup", EXIT_FAILURE);
	}
	free(user_input);
	free_path_dir(*head);
	error_handling("malloc", EXIT_FAILURE);
}

/**
 * build_path_list - gets, slices and stores
 * the value of the environment variable in a linked list
 * @head: head of the linked list
 * @name: name of the environment variable
 * @user_input: raw user input
 *
 * Return: the head of the built linked list
 * or NULL if the PATH is not specified
 */
dir_t *build_path_list(dir_t **head, char *name, char *user_input)
{
	char *token = NULL;
	char *cpy_path_pathes = NULL;
	/* Stores the value of the requested environment variable */
	char *path_pathes;

	if (name != NULL)
	{
		/* Create a copy so as not to destroy the original */
		path_pathes = _getenv(name);
		cpy_path_pathes = strdup(path_pathes);
		if (cpy_path_pathes != NULL)
		{
			/* Tokenises file paths and stores them in a linked list */
			token = strtok(cpy_path_pathes, ":");
			while (token)
			{
				/* Create a new node and store path in it */
				create_node_at_end(head, name, token, user_input);
				token = strtok(NULL, ":");
			}

			/* Cleanses the memory */
			free(cpy_path_pathes);

			return (*head);
		}
		free(user_input);
		error_handling("strdup", EXIT_FAILURE);
	}
	return (NULL);
}
