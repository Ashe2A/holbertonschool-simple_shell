#include "simple_shell.h"

/**
 * _exit_function - exits the simple shell (needs to free mallocs)
 * @user_input: to free
 * @tokens: to free
 * @child_status: exit code of the child process
 */
void _exit_function(char *user_input, char **tokens, int child_status)
{
	if (user_input != NULL && tokens != NULL)
	{
		free(user_input);
		user_input = NULL;
		free_tokens(tokens);

		if (child_status != 0)
			exit(child_status);

		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
