#include "simple_shell.h"

/**
 * check_and_run_builtin - call the built-in function
 * corresponding to the command if it exists.
 * @user_input: is an array of character strings
 * containing the raw data entered by the user
 * @tokens: is an array of pointers to character strings
 * containing the command and arguments given by the user
 *
 * Return: 1 for built-in mode, 0 otherwise
 */
int check_and_run_builtin(char *user_input, char **tokens)
{
	/* The structure storing the command and its built-in function */
	built_in_t built_in_list[] = {
		{"env", _printenv},
		{"exit", _exit_function},
		{NULL, NULL}
	};
	int i = 0;

	/* Compare user's input with cmd from structure and run function if found */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(tokens[0], built_in_list[i].cmd) == 0)
		{
			built_in_list[i].f(user_input, tokens);
			/* Built-in mode on */
			return (EXIT_FAILURE);
		}
		i++;
	}

	/* Built-in mode on */
	return (0);
}
