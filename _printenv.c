#include "simple_shell.h"

/**
 * _printenv - print the environment variables
 * @user_input: unused parameter
 * @tokens: unsused parameter
 * @child_status: unsused parameter
 *
 * Description: This function prints all the environment variables
 * available in the current shell session. The function does not
 * return any value.
 *
 * Return: Always void
 */
void _printenv(char *user_input __attribute__((unused)),
char **tokens __attribute__((unused)), int child_status)
{
	int i = 0;

	(void)child_status;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
