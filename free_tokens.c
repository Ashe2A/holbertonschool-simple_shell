#include "simple_shell.h"

/**
 * free_tokens - frees the memory of tokens
 * @tokens: is the double array to free
 *
 * Return: Always nothing
 */
void free_tokens(char **tokens)
{
	char **current = tokens;

	/* Don't execute the function if tokens is empty */
	if (tokens == NULL)
		return;

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
