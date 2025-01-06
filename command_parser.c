#include "shell.h"

/**
 * split_command - Splits command line into tokens
 * @command_line: Command line to split
 * Return: Array of tokens or NULL on failure
 */
char **split_command(char *command_line)
{
	char **args = NULL;
	char *token = NULL;
	char *delimiter = " \n\t\r";
	int token_count = 0;
	cleanup_t *cleanup_data;

	cleanup_data = create_cleanup_info(command_line, NULL, NULL);
	if (!cleanup_data)
		return (NULL);

	args = malloc(sizeof(char *) * MAX_TOKENS);
	if (!args)
	{
		free(cleanup_data);
		display_error("malloc", EXIT_FAILURE);
		return (NULL);
	}

	token = strtok(command_line, delimiter);
	while (token && token_count < MAX_TOKENS - 1)
	{
		args[token_count] = strdup(token);
		if (!args[token_count])
		{
			clean_command_array(args);
			free(cleanup_data);
			display_error("strdup", EXIT_FAILURE);
			return (NULL);
		}
		token = strtok(NULL, delimiter);
		token_count++;
	}
	args[token_count] = NULL;

	free(cleanup_data);
	return (args);
}

/**
 * clean_command_array - Frees array of command arguments
 * @args: Array to free
 */
void clean_command_array(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}

	free(args);
}

/**
 * is_empty_string - Checks if string contains only spaces
 * @str: String to check
 * Return: 1 if empty, 0 if not
 */
int is_empty_string(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}
