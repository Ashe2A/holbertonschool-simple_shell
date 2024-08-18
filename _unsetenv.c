#include "simple_shell.h"

int search_delete_index(const char *name, int name_len, int i);
char **copy_without_del_index(int i, int del_index, int array_len);

/**
 * _unsetenv - deletes the variable name from the environment.
 * @name: is a string containing the serached variable
 *
 * Return: return zero on success, or -1 on error
 */
int _unsetenv(const char *name)
{
	int name_len = 0;
	char **new_env = NULL;
	int i = 0;
	int del_index = 0, array_len = 0;

	if (name == NULL)
		return (-1);

	name_len = strlen(name);

	/* Get the index to delete */
	del_index = search_delete_index(name, name_len, i);

	/*  If not find */
	if (custom_environ[del_index] == NULL)
		return (0);

	/* Get the array's size */
	while (custom_environ[array_len])
		array_len++;

	/* Create and copy a new array */
	new_env = copy_without_del_index(i, del_index, array_len);

	/* Free old allocation of custom_environ */
	for (i = 0; i < array_len; i++)
		free(custom_environ[i]);
	free(custom_environ);

	/* Set the custom_environ to the new one */
	custom_environ = new_env;

	return (0);
}

/**
 * search_delete_index - compares the name gives
 * by the user and the name in the array
 * @name: is a string to compare
 * @name_len: is an integer to use with strncmp
 * @i: is an integer to catch the index to delete
 *
 * Return: the index to delete
 */
int search_delete_index(const char *name, int name_len, int i)
{
	/* Search for index to delete */
	while (custom_environ[i])
	{
		if (strncmp(name, custom_environ[i], name_len) == 0
		&& custom_environ[i][name_len] == '=')
		{	/* Get the index where the variable to delete */
			break;
		}
		i++;
	}
	return (i);
}

/**
 * copy_without_del_index - copy the array in a new one
 * by skipping the index to delete
 * @i: is an integer to catch the index to delete
 * @del_index: is an integer to stores the index where the var to delete is
 * @array_len: is an integer to stores the length of array
 *
 * Return: the new array
 */
char **copy_without_del_index(int i, int del_index, int array_len)
{
	char **new_env = malloc(sizeof(char *) * (array_len));

	if (new_env == NULL)
		error_handling("malloc", EXIT_FAILURE);

	/* Copy first part of array */
	for (i = 0; i < del_index; i++)
		new_env[i] = strdup(custom_environ[i]);

	/* Check the end of array */
	if (custom_environ[del_index + 1])
		/* Add the second part, deleted index is skipped */
		for (i = del_index + 1; i < array_len; i++)
			new_env[i - 1] = strdup(custom_environ[i]);

	/* NULL termination */
	new_env[i] = NULL;

	return (new_env);
}
