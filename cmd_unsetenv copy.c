#include "simple_shell.h"

/**
 * cmd_unsetenv - links to unsetenv function in built-in mode
 * @user_input: unused
 * @tokens: is the command and arguments
 *
 * Return: Always nothing
 */
void cmd_unsetenv(char *user_input __attribute__((unused)), char **tokens)
{
	if (tokens[1])
		_unsetenv(tokens[1]);
	else
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
}
