#include "simple_shell.h"

/**
 * check_and_run_builtin - call built-in function if user_input match
 * @user_input: to check
 *
 * Return: 0 for no built-in mode, 1 for built-in
 */
int check_and_run_builtin(char *user_input, char **av)
{
	built_in_t built_in_list[] = {
		{"env\n", _printenv},
		{"cd\n", change_directory},
		{NULL, NULL}
	};
	int i = 0;
	int built_in_mode = 0;

	/* Compare user's input with cmd from structure an f run function if find */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(user_input, built_in_list[i].cmd) == 0)
			built_in_list[i].f(user_input, av);

		i++;
	}

	/* If command is not found, no built-in mode */
	if (built_in_list[i].cmd != NULL)
		built_in_mode = 1;

	return (built_in_mode);
}
