#include "simple_shell.h"

/**
 * execve_and_check - the command of the user
 * @tokens: is an array of pointers to the extracted tokens
 * @full_path: is string storing the building full path of command
 * @env: is an array of pointers storing
 * @user_input: is an array of character strings
 * containing the raw data entered by the user
 * the environment variables and his values
 *
 * Return: (Always nothing)
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
