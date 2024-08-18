#include "simple_shell.h"

/**
 * create_custom_environ - create a full malloc'ed environment
 *
 * Return: a custom environment
 */
char **create_custom_environ(void)
{
	int env_size = 0;
	int i = 0, j = 0;
	char **custom_environ = NULL;

	/* Get the size of environment stored in environ */
	while (environ[env_size])
		env_size++;

	/* Allocate memory in relation to the size of environ + NULL termination */
	custom_environ = malloc(sizeof(char *) * (env_size + 1));
	if (custom_environ == NULL)
		error_handling("malloc", EXIT_FAILURE);

	/* Copy all the variables */
	for (i = 0; i < env_size; i++)
	{
		custom_environ[i] = strdup(environ[i]);
		if (custom_environ[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(custom_environ[j]);
			free(custom_environ);
			error_handling("malloc", EXIT_FAILURE);
		}
	}

	/* NULL terminate the customm environment array */
	custom_environ[i] = NULL;

	return (custom_environ);
}
