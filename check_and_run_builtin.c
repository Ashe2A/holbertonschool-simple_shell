#include "simple_shell.h"

/**
 * check_and_run_builtin - call the built-in function
 * of the corresponding token if exists
 * @user_input: is an array of character strings
 * containing the raw data entered by the user
 * @tokens: is an array of pointers to character strings
 * containing the command and arguments given by the user
 *
 * Return: 0 for no built-in mode, 1 for built-in
 */
int check_and_run_builtin(char *user_input, char **tokens)
{
	built_in_t built_in_list[] = {
		{"env", _printenv},
		{"exit", _exit_function},
		{NULL, NULL}
	};
	int i = 0;
	int built_in_mode = 0;

	/* Compare user's input with cmd from structure an f run function if find */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(tokens[0], built_in_list[i].cmd) == 0)
			built_in_list[i].f(user_input, tokens);

		i++;
	}

	/* If command is not found, no built-in mode */
	if (built_in_list[i].cmd != NULL)
		built_in_mode = 1;

	return (built_in_mode);
}
