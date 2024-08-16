#include "simple_shell.h"

/**
 * path_parse - builds and compares the path file
 * @command: is a character string containing the command to be checked
 *
 * Description: The builded pathfile is compared with the value
 * of the PATH environment variable. It checks whether the file exists
 *
 * Return: the full filepath or NULL if it not exists
 */
char *path_parse(char *command)
{
	char *full_path = NULL; /* Stores a path with command to test */
	dir_t *head = NULL, *curr_node = NULL;
	int path_length = 0;
	char *env_var = "PATH";	/* Stores the path of executables */

	if (command == NULL)
		return (NULL);

	head = build_path_list(&head, env_var);
	curr_node = head;

	while (curr_node != NULL)
	{
		path_length = strlen(curr_node->path) + strlen(command);

		full_path = malloc(sizeof(char) * (path_length + 2));
		if (full_path == NULL)
			error_handling("malloc", EXIT_FAILURE);

		strcpy(full_path, curr_node->path);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, F_OK) == 0)
		{
			free_path_dir(head);
			return (full_path);
		}

		free(full_path);
		full_path = NULL;
		curr_node = curr_node->next;
	}

	free_path_dir(head);

	return (NULL); /* If path is not found */
}
