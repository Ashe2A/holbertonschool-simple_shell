#include "shell.h"

/**
 * clean_resources - Frees all allocated resources
 * @args: Command arguments to free
 * @path: Command path to free
 * @is_full_path: Indicates if path needs to be freed
 * @command_line: Command line (unused)
 * @read_size: Size of command line (unused)
 */
void clean_resources(char **args, char *path,
		int is_full_path, char *command_line,
		int read_size __attribute__((unused)))
{
	(void)command_line;

	if (path && !is_full_path)
	{
		free(path);
		path = NULL;
	}

	if (args)
	{
		clean_command_array(args);
		args = NULL;
	}
}

/**
 * safe_malloc - Allocates memory with error handling
 * @size: Size to allocate
 * @cleanup: Cleanup info for error handling
 * Return: Pointer to allocated memory
 */
void *safe_malloc(size_t size, cleanup_t *cleanup)
{
	void *ptr = malloc(size);

	if (!ptr)
	{
		if (cleanup)
		{
			if (cleanup->command_line)
				free(cleanup->command_line);
			if (cleanup->args)
				clean_command_array(cleanup->args);
			if (cleanup->path)
				free(cleanup->path);
			free(cleanup);
		}
		display_error("malloc", EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * safe_strdup - Duplicates string with error handling
 * @str: String to duplicate
 * @cleanup: Cleanup info for error handling
 * Return: Pointer to new string
 */
char *safe_strdup(const char *str, cleanup_t *cleanup)
{
	char *new_str;

	if (!str)
		return (NULL);

	new_str = strdup(str);
	if (!new_str)
	{
		if (cleanup)
		{
			if (cleanup->command_line)
				free(cleanup->command_line);
			if (cleanup->args)
				clean_command_array(cleanup->args);
			if (cleanup->path)
				free(cleanup->path);
			free(cleanup);
		}
		display_error("strdup", EXIT_FAILURE);
	}
	return (new_str);
}
