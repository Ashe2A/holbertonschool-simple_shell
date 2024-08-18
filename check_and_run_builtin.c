#include "simple_shell.h"

/**
 * check_and_run_builtin - call built-in function if user_input match
 * @user_input: to check
 * @tokens: is an array of pointers stored arguments
 *
 * Return: 0 for no built-in mode, 1 for built-in
 */
int check_and_run_builtin(char *user_input, char **tokens)
{
	built_in_t built_in_list[] = {
		{ "env", _printenv },
		{ "cd", change_directory },
		{ "exit", _exit_function },
		{ "setenv", cmd_setenv },
		{ "unsetenv", cmd_unsetenv },
		{ NULL, NULL }
	};
	int i = 0;
	int built_in_mode = 0;

	/* Compare user's input with cmd from structure an f run function if find */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(tokens[0], built_in_list[i].cmd) == 0)
		{
			built_in_list[i].f(user_input, tokens);
			break;
		}

		i++;
	}

	/* If command is not found, no built-in mode */
	if (built_in_list[i].cmd != NULL)
		built_in_mode = 1;

	return (built_in_mode);
}
