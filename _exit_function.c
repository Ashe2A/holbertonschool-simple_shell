#include "simple_shell.h"

/**
 * _exit_function - exit the simple shell (needs to free allocs)
 * @user_input: to free
 * @tokens: to free
 *
 * Return: the code of the status
 */
void _exit_function(char *user_input, char **tokens)
{
	if (user_input == NULL || tokens == NULL)
		exit(EXIT_FAILURE);

	free(user_input);
	user_input = NULL;
	free_tokens(tokens);
	printf("\n");
	exit(EXIT_SUCCESS);
}
