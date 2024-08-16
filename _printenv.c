#include "simple_shell.h"

/**
 * _printenv - print the environments variables
 * @user_input: unused
 *
 * Return: Always nothing
 */
void _printenv(char *user_input __attribute__((unused)))
{
	char **cpy_environ = environ;

	printf("%s\n", *cpy_environ);
}
