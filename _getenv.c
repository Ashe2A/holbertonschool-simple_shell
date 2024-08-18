#include "simple_shell.h"

/**
 * _getenv - return the value of searched environment variable
 * @name:is a string storing the name of the searched variable
 *
 * Description:  The getenv() function searches the environment list
 * to find the environment variable name,
 * and returns a pointer to the corresponding value string
 *
 * Return: the value of chosen environment variable, NULL if not found
 */
char *_getenv(const char *name)
{
	size_t name_len = 0;

	if (name == NULL || environ == NULL)
		return (NULL);

	/* Compute the length of name */
	name_len = strlen(name);

	/* Traverse the array */
	while (*environ != NULL)
	{
		/* Compares name and its length with that of the variable */
		/* Make sure that the name really ends in the same place */
		if (strncmp(name, *environ, name_len) == 0 && (*environ)[name_len] == '=')
			/* Return a pointer the '=' character */
			return (*environ + name_len + 1);

		environ++;
	}
	return (NULL);
}
