#include "simple_shell.h"

/**
 * child_error_handling - handles errors for a child process
 * @msg: to display when an error occurs
 * @exit_code: of the child process
 *
 * Description: This function prints an error message using "perror"
 * and exits the child process with the specified exit code. It uses
 * _exit that avoid interference with the parent like unnecessary clean-up.
 */
void child_error_handling(char *msg, int exit_code)
{
	perror(msg);
	/* No need for a full clean to exit a child process, */
	/* as it's instantly destroyed */
	_exit(exit_code);
}

/**
 * execve_and_check - checks and ultimately executes a command
 * @tokens: tokenized user input
 * @full_path: path of the input command (which)
 * @env: environment variables and their values
 * @user_input: raw data entered by the user
 */
void execve_and_check(char **tokens, char *full_path,
char **env, char *user_input)
{
	if (execve(full_path, tokens, env) == -1)
	{
		free(user_input);
		cleanup_tokens_and_path(tokens, full_path);	/* Memory clean up */
		child_error_handling("execve", EXIT_FAILURE);
	}
}
