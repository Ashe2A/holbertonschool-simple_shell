#include "hsh.h"

/**
 * _getenv - return the value of chosen environment variable
 * @name:is a string that stores the name of the variable
 *
 * Return: the value of chosen environment variable
 */
char *_getenv(const char *name)
{
	size_t length = strlen(name);

	if (name == NULL || environ == NULL)
		return (NULL);
	while (*environ != NULL)
	{
		if (strncmp(name, *environ, length) == 0 && (*environ)[length] == '=')
			return (*environ + length + 1);

		environ++;
	}
	return (NULL);
}
