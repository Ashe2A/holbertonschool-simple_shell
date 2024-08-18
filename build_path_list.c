#include "simple_shell.h"

/**
 * build_path_list - gets, slices and stores
 * the value of the environment variable in a linked list
 * @head: is a pointer to the start of a linked list
 * @name: is a character string containing
 * the name of an environment variable
 *
 * Return: the head of the constructed linked list
 * or NULL if the PATH is not specified
 */
dir_t *build_path_list(dir_t **head, char *name)
{
	char *token = NULL;
	char *cpy_path_pathes = NULL;
	/* Stores the value of the requested environment variable */
	char *path_pathes = _getenv(name);

	if (name == NULL)
		return (NULL);

	/* Create a copy so as not to destroy the original */
	cpy_path_pathes = strdup(path_pathes);
	if (cpy_path_pathes == NULL)
		error_handling("strdup", EXIT_FAILURE);

	/* Tokenises file paths and stores them in a linked list */
	token = strtok(cpy_path_pathes, ":");
	while (token)
	{
		/* Create a new node and store path in it */
		create_node(head, name, token);
		token = strtok(NULL, ":");
	}

	/* Cleanses the memory */
	free(cpy_path_pathes);

	return (*head);
}
