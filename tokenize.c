#include "simple_shell.h"

/**
 * tokenize_input - tokenize an input
 * @ui: input to tokenize
 * @tokens: result (input into tokens)
 * @token: each token
 * @delim: token delimiter
 * @token_count: is the number of tokens in the string
 *
 * Return: an array of pointers pointin arrays
 */
char **tokenize_input(char *ui, char **tokens, char *token,
					char *delim, int token_count)
{
	int i = 0; /* Index for tokens */

	/* Allocate memory for tokens + 1 to NULL terminate the array */
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (tokens == NULL)
	{
		free(ui);
		ui = NULL;
		error_handling("malloc", EXIT_FAILURE);
	}

	/* Tokenize user input */
	token = strtok(ui, delim);
	while (token)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			while (tokens[i])
				free(tokens[--i]);
			free(tokens);
			free(ui);
			error_handling("tokens", 1);
		}
		i++;
		token = strtok(NULL, delim);
	}

	/* Null terminate the array of pointer */
	tokens[i] = NULL;

	return (tokens);
}

/**
 * tokenize - create an arrays of tokens
 * @user_input: to tokenize
 *
 * Return: an array of tokens
 */
char **tokenize(char *user_input)
{
	char **tokens = NULL; /* Array of pointers pointing tokens */
	char *token = NULL; /* Word cutting from user_input by strtok */
	char *delimiter = " \n";  /* Delimits the tokens */
	int token_count = 0;	/* Stores the number of tokens in unsr_input */
	char *cp_input = NULL;	/* Create a copy to count number of tokens */

	/* Copy user_ input and error hanling */
	cp_input = strdup(user_input);
	if (cp_input == NULL)
	{
		free(user_input);
		user_input = NULL;
		error_handling("strdup", EXIT_FAILURE);
	}

	/* Count the number of tokens */
	token = strtok(cp_input, delimiter);
	while (token)
	{
		token_count++;
		token = strtok(NULL, delimiter);
	}
	free(cp_input); /* Free the copy */
	cp_input = NULL;

	tokens = tokenize_input(user_input, tokens, token, delimiter, token_count);

	return (tokens);
}
