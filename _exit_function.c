#include "simple_shell.h"

/**
 * _exit_function - exit the simple shell (needs to free allocs)
 * @user_input: to free
 * @tokens: to free
 * @child_status: is an integer storing the exit code of th child
 *
 * Return: the code of the child's status
 */
void _exit_function(char *user_input, char **tokens, int child_status)
{
	if (user_input == NULL || tokens == NULL)
		exit(EXIT_FAILURE);

	free(user_input);
	user_input = NULL;
	free_tokens(tokens);

	if (child_status != 0)
		exit(child_status);

	exit(EXIT_SUCCESS);
}
