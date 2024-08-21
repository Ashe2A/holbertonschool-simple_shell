#include "simple_shell.h"

/**
 * free_tokens - frees the memory of tokens
 * @tokens: to free
 */
void free_tokens(char **tokens)
{
	char **current;

	/* Don't execute the function if tokens is empty */
	if (tokens != NULL)
	{
		current = tokens;
		while (*current != NULL)
		{
			/* Free each token and give it the value NULL */
			free(*current);
			*current = NULL;
			current++;
		}

		/* Free the array of pointers and give it the value NULL */
		free(tokens);
		tokens = NULL;
	}
}

/**
 * cleanup_tokens_and_path - frees allocated memory from tokens and full_path
 * @tokens: to free
 * @full_path: to free
 */
void cleanup_tokens_and_path(char **tokens, char *full_path)
{
	/* Defensive programming */
	if (full_path != NULL)
	{
		free(full_path);
		full_path = NULL;
	}

	/* Free all tokens */
	free_tokens(tokens);
}