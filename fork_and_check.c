#include "simple_shell.h"

/**
 * fork_and_check - creates a child process
 * and checks that creation has not failed
 * @tokens: to be freed in the event of default
 * @full_path: to be freed in the event of default
 * @child_pid: is the number of created process
 * @user_input: is an array of character strings
 * containing the raw data entered by the user
 *
 * Return: the child's pid or exit if unsuccessful
 */
pid_t fork_and_check(char **tokens, char *full_path,
		pid_t *child_pid, char *user_input)
{
	/* Create a child process */
	*child_pid = fork();

	/* Return -1 if fails */
	if (*child_pid == -1)
	{
		/* Memory clean up */
		free(user_input);
		cleanup_tokens_and_path(tokens, full_path);

		/* Display an error message and exit the program */
		error_handling("fork", EXIT_FAILURE);
	}

	return (*child_pid);
}
