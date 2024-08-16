#include "simple_shell.h"

/**
 * _exit_function - exit the simple shell (needs to free allocs)
 * @user_input: unused
 * @argv: unused
 */
void _exit_function(char *user_input, char **argv __attribute__((unused)))
{
	free(user_input);
	_exit(0);
}
