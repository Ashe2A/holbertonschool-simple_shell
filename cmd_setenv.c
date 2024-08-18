#include "simple_shell.h"

/**
 * cmd_setenv - links to setenv function in built-in mode
 * @user_input: unused
 * @tokens: is the command and arguments
 *
 * Return: Always nothing
 */
void cmd_setenv(char *user_input __attribute__((unused)), char **tokens)
{
	if (tokens[1])
		_setenv(tokens[1], tokens[2], 1);
	else
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
}
