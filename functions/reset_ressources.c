#include "simple_shell.h"

/**
 * reset_ressources - frees memory if necessary
 * @tokens: to free
 * @full_path: to free
 * @is_full_path: 1 if user input has command (stored a linked list), 0 if not
 * @user_input: raw source user input
 * @read: number of characters of the user input (counted by getline())
 */
void reset_ressources(char **tokens, char *full_path, int is_full_path,
	char *user_input, int read)
{
	if ((user_input[0] != '\n') && (read != 1))
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
