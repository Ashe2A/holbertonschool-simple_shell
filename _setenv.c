#include "simple_shell.h"

int modify_env(const char *name, const char *value,
	int overwrite, int name_len, int value_len);
int add_env(const char *name, const char *value,
	int env_size, int name_len, int value_len);

/**
 * _setenv - add or modify a environment variable
 * @name: is a string storing the variable's name
 * @value: is a string storing the variable's value
 * @overwrite: 0 if false, 1 if true
 *
 * Decription: causes memory leak
 *
 * Return: zero on success, or -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int env_size = 0;
	size_t name_len = 0;
	size_t value_len = 0;

	if (name == NULL || value == NULL || custom_environ == NULL)
		return (-1);

	name_len = strlen(name);
	value_len = strlen(value);


	/* We've already been through the array we know its size */
	env_size = modify_env(name, value, overwrite, name_len, value_len);
	if (env_size == 0)
		return (0);

	/* If the var's name don't exist, so add it */
	add_env(name, value, env_size, name_len, value_len);

	return (0);
}

/**
 * modify_env - modify a environment variable
 * @name: is a string storing the variable's name
 * @value: is a string storing the variable's value
 * @overwrite: 0 if false, 1 if true
 * @name_len: of the environment variable
 * @value_len: of the environment variable
 *
 * Decription: causes memory leak
 *
 * Return: zero on success, or -1 on error
 */
int modify_env(const char *name, const char *value,
int overwrite, int name_len, int value_len)
{
	int i = 0;
	char *new_var = NULL;

	/* Check if the variable already exists */
	while ((custom_environ)[i] != NULL)
	{
		if (strncmp((custom_environ)[i], name, name_len) == 0 &&
		(custom_environ)[i][name_len] == '=')
		{
			if (overwrite == 0)
				return (0); /* Don't overwrite existing variable */

			/* Overwrite the existing variable */
			new_var = malloc(name_len + value_len + 2);
			if (new_var == NULL)
				error_handling("malloc", EXIT_FAILURE);

			sprintf(new_var, "%s=%s", name, value);
			free(custom_environ[i]);
			(custom_environ)[i] = new_var;

			return (0);
		}
		i++;
	}
	return (i);
}

/**
 * add_env - add a environment variable
 * @name: is a string storing the variable's name
 * @value: is a string storing the variable's value
 * @env_size: is a integer storing the variable's size
 * @name_len: of the environment variable
 * @value_len: of the environment variable
 *
 * Decription: causes memory leak
 *
 * Return: zero on success, or -1 on error
 */
int add_env(const char *name, const char *value,
int env_size, int name_len, int value_len)
{
	int i = 0;
	char *new_var = NULL;
	char **new_env = NULL;

	/* Need to add a new variable, extend the array */
	new_env = malloc(sizeof(char *) * (env_size + 2));
	if (new_env == NULL)
		error_handling("malloc", EXIT_FAILURE);

	/* Copy old environment variables to new array */
	for (i = 0; i < env_size; i++)
		new_env[i] = custom_environ[i];

	/* Add the new variable */
	new_var = malloc(name_len + value_len + 2);
	if (new_var == NULL)
	{
		free(new_env);
		error_handling("malloc", EXIT_FAILURE);
	}

	sprintf(new_var, "%s=%s", name, value);
	new_env[env_size] = new_var;
	new_env[env_size + 1] = NULL;

	/* Free the old environment array and set the new one */

	free(custom_environ);
	custom_environ = new_env;

	return (0);
}
