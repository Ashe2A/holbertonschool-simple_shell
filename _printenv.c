#include "simple_shell.h"

/**
 * _printenv - print the environment variables
 * @user_input: user input (unused)
 * @tokens: tokenized user input (unused)
 * @child_status: exit code of the child process (unused)
 *
 * Description: This function prints all the environment variables
 * available in the current shell session. The function does not
 * return any value.
 */
void _printenv(char *user_input __attribute__((unused)),
	char **tokens __attribute__((unused)),
	int child_status __attribute__((unused))
	)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
