#include "hsh.h"

/**
 * execve_and_check - the command of the user
 * @tokens: is an array of pointers to the extracted tokens
 * @full_path: is string storing the building full path of command
 * @env: is an array of pointers storing
 * the environment variables and his values
 *
 * Return: (Always nothing)
 */
void execve_and_check(char **tokens, char *full_path, char **env)
{
	if (execve(full_path, tokens, env) == -1)
	{
		cleanup_tokens_and_path(tokens, full_path);	/* Memory clean up */
		child_error_handling("execve", EXIT_FAILURE);
	}
}
