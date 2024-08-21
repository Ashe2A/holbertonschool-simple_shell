#include "simple_shell.h"

/**
 * check_and_run_builtin - call built-in functions if it's one
 * @user_input: user input with the possible built-in
 * @tokens: tokenized user input
 * @child_status: exit code of the child process
 *
 * Return: 1 if it's a built-in, 0 otherwise
 */
int check_and_run_builtin(char *user_input, char **tokens, int child_status)
{
	/* Built-in functions and their corresponding calls */
	built_in_t built_in_list[] = {
		{"env", _printenv},
		{"exit", _exit_function},
		{NULL, NULL}
	};
	int i = 0;

	/* Compare user input with structure commands and run if found */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(tokens[0], built_in_list[i].cmd) == 0)
		{
			built_in_list[i].f(user_input, tokens, child_status);
			return (1); /* Built-in mode on */
		}
		i++;
	}

	return (0); /* Built-in mode off */
}
