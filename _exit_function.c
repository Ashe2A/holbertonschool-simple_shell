#include "simple_shell.h"

/**
 * _exit_function - exit the simple shell (needs to free allocs)
 * @user_input: to free
 * @tokens: to free
 */
void _exit_function(char *user_input, char **tokens)
{
	free(user_input);
	free(tokens);
	exit(EXIT_SUCCESS);
}
