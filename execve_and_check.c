#include "simple_shell.h"

/**
 * execve_and_check - the command of the user
 * @tokens: is an array of pointers to the extracted tokens
 * @full_path: is string storing the building full path of command
 * the environment variables and his values
 *
 * Return: (Always nothing)
 */
void execve_and_check(char **tokens, char *full_path)
{
	if (execve(full_path, tokens, custom_environ) == -1)
	{
		cleanup_tokens_and_path(tokens, full_path);	/* Memory clean up */
		child_error_handling("execve", EXIT_FAILURE);
	}
}
