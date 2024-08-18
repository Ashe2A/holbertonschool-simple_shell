#include "simple_shell.h"

/**
 * _getenv - return the value of chosen environment variable
 * @name:is a string that stores the name of the variable
 *
 * Return: the value of chosen environment variable
 */
char *_getenv(const char *name)
{
	size_t length = strlen(name);
	char **env = custom_environ;

	if (*name == '\0' || custom_environ == NULL)
		return (NULL);

	while (*env != NULL)
	{
		/* Compare name with the list and ensure that is has the good length */
		if (strncmp(name, *env, length) == 0 && (*env)[length] == '=')
			/* Put the pointer after '=' to display variable value */
			return (*env + length + 1);

		env++;
	}
	return (NULL);
}
