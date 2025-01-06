#include "shell.h"

/**
 * get_env_value - Gets value of environment variable
 * @name: Name of environment variable
 * Return: Value of environment variable or NULL if not found
 */
char *get_env_value(const char *name)
{
	int i = 0;
	size_t name_len;

	if (!name || !environ)
		return (NULL);

	name_len = strlen(name);

	while (environ[i])
	{
		if (strncmp(name, environ[i], name_len) == 0 &&
				environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}

	return (NULL);
}

/**
 * find_command_path - Searches command in PATH directories
 * @command: Command to find
 * @command_line: Original command line
 * Return: Full path of command or NULL if not found
 */
char *find_command_path(char *command, char *command_line)
{
	char *path_value, *path_copy, *full_path;
	char *token;
	size_t path_len;

	path_value = get_env_value("PATH");
	if (!path_value)
		return (NULL);

	path_copy = strdup(path_value);
	if (!path_copy)
	{
		free(command_line);
		display_error("strdup", EXIT_FAILURE);
	}

	token = strtok(path_copy, ":");
	while (token)
	{
		path_len = strlen(token) + strlen(command) + 2;
		full_path = malloc(path_len);
		if (!full_path)
		{
			free(path_copy);
			free(command_line);
			display_error("malloc", EXIT_FAILURE);
		}

		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
