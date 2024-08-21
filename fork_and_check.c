#include "simple_shell.h"

/**
 * fork_and_check - creates and checks a child process
 * @tokens: tokenized user input to free if fork fails
 * @full_path: of the command to free if fork fails 
 * @child_pid: process ID of the command process
 * @user_input: raw data entered by the user
 *
 * Return: the child process' ID or exit if fork fails
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
