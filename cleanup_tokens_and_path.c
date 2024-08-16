#include "simple_shell.h"

/**
 * cleanup_tokens_and_path - frees allocated memory from tokens and full_path
 * @tokens: to free
 * @full_path: to free
 *
 * Return: Always nothing
 */
void cleanup_tokens_and_path(char **tokens, char *full_path)
{
	/* Defensive programming */
	if (full_path != NULL)
	{
		free(full_path);
		full_path = NULL;
	}

	/* Call functions to free tokens */
	free_tokens(tokens);
}
