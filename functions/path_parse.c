#include "simple_shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable to look for
 *
 * Description:  The getenv() function searches the environment list
 * to find the environment variable name,
 * and returns a pointer to the corresponding value string
 *
 * Return: the value of the environment variable, NULL if not found
 */
char *_getenv(const char *name)
{
	size_t name_len = 0;
	int i = 0;

	if ((name != NULL) && (environ != NULL))
	{
		/* Compute the length of name */
		name_len = strlen(name);

		/* Traverse the array */
		while (environ[i] != NULL)
		{
			/* Compares name and its length with that of the variable */
			/* Make sure that the name really ends in the same place */
			if ((strncmp(name, environ[i], name_len) == 0)
				&& ((environ[i])[name_len] == '='))
			/* Return a pointer the '=' character */
				return (environ[i] + name_len + 1);
			i++;
		}
	}
	return (NULL);
}

/**
 * free_path_dir - frees a singly linked list
 * @head: head of the list
 */
void free_path_dir(dir_t *head)
{
	dir_t *curr_node = NULL;

	while (head != NULL)
	{
		curr_node = head; /* Stores the current node */
		head = head->next; /* Move head to the next node */

		/* Free the elements of the node and assign it the value NULL */
		free(curr_node->name);
		curr_node->name = NULL;

		free(curr_node->path);
		curr_node->path = NULL;

		free(curr_node); /* Free the node */
		curr_node = NULL;
	}
}

/**
 * path_parse - builds and compares the path file with the command's
 * @command: the command to be checked
 * @user_input: user input (command + args)
 *
 * Description: The builded pathfile is compared with the value
 * of the PATH environment variable. It checks whether the file exists
 *
 * Return: full path of the commands' file or NULL if not found
 */
char *path_parse(char *command, char *user_input)
{
	char *full_path = NULL; /* Stores a path with command to test */
	dir_t *head = NULL, *curr_node = NULL;
	int path_length = 0;
	char *env_var = "PATH";	/* Stores the path of executables */

	if (_getenv(env_var) != NULL) /* Don't execute if no PATH */
	{
		/*** malloc ***/
		head = build_path_list(&head, env_var, user_input);
		curr_node = head;

		while (curr_node != NULL)
		{
			path_length = strlen(curr_node->path) + strlen(command);

			full_path = malloc(sizeof(char) * (path_length + 2));
			if (full_path == NULL)
			{
				free(user_input);
				free_path_dir(head);
				error_handling("malloc", EXIT_FAILURE);
			}
			strcpy(full_path, curr_node->path);
			strcat(full_path, "/");
			strcat(full_path, command);

			if (access(full_path, X_OK) == 0)
			{
				free_path_dir(head);
				return (full_path);
			}
			free(full_path);
			full_path = NULL;
			curr_node = curr_node->next;
		}

		free_path_dir(head);
	}
	return (NULL);
}
