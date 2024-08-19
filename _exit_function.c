#include "simple_shell.h"

/**
 * _exit_function - exit the simple shell (needs to free allocs)
 * @user_input: to free
 * @tokens: unused
 */
void _exit_function(char *user_input, char **tokens __attribute__((unused)))
{
	free(user_input);
	exit(EXIT_SUCCESS);
}
