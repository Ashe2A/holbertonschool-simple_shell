#include "simple_shell.h"

/**
 * _printenv - print the environments variables
 * @user_input: unused
 * @tokens: unsused
 *
 * Return: Always nothing
 */
void _printenv(char *user_input __attribute__((unused)),
	char **tokens __attribute__((unused)))
{
	char **cpy_environ = custom_environ;

	while (*cpy_environ)
	{
		printf("%s\n", *cpy_environ);
		cpy_environ++;
	}
}
