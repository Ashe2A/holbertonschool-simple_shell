#include "simple_shell.h"

/**
 * reset_ressources - frees memory if necessary
 * @tokens: to free
 * @full_path: to free
 * @is_full_path: indicates whether the user has entered the command
 * with its access path.
 * @user_input: is the source input entered by the user
 * @read: is the number of character read in the user input
 * by the system call getline
 *
 * Return: Always nothing
 */
void reset_ressources(char **tokens, char *full_path, int is_full_path,
	char *user_input, int read)
{

	if (user_input[0] != '\n' && read != 1)
	{
		/* Edge case: if the user input a full path command */
		if (is_full_path == 0)
		{
			/* Don't free full_path because it had the same address as tokens[0] */
			/* Else double free */
			free_tokens(tokens);
		}
		else
			cleanup_tokens_and_path(tokens, full_path);	/* Memory clean up */
	}
}
