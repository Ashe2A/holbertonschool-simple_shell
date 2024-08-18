#include "simple_shell.h"

/**
 * _printenv - print the environment variables
 * @user_input: unused parameter
 * @tokens: unsused parameter
 *
 * Description: This function prints all the environment variables
 * available in the current shell session. The function does not
 * return any value.
 *
 * Return: Always void
 */
void _printenv(char *user_input __attribute__((unused)),
			char **tokens __attribute__((unused)))
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
