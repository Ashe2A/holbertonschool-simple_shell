#include "simple_shell.h"

/**
 * tokenize_input - tokenize an input
 * @ui: input to tokenize
 * @tokens: result (input into tokens)
 * @token: each token
 * @delim: token delimiter
 * @i: token counter
 *
 * Return: the token list (result)
 */
char **tokenize_input(char *ui, char **tokens, char *token, char *delim, int i)
{
	tokens = malloc(sizeof(tokens[i]));
	tokens[i] = strdup(token);
	if (tokens[i] == NULL)
	{
		while (tokens[i])
			free(tokens[--i]);
		free(tokens);
		free(ui);
		error_handling("tokens", 1);
		return (NULL);
	}
	token = strtok(NULL, delim);
	return (tokens);
}

/**
 * count_tokens - Count the number of tokens
 * @token: each token
 * @cp_input: copy to count number of tokens
 * @delim: token delimiter
 *
 * Return: number of tokens
 */
int count_tokens(char *token, char *cp, char *delim)
{
	int count = 0;

	token = strtok(cp, delim);
	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(cp); /* Free the copy */
	cp = NULL;
	return (count);
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
	int i = 0; /* Index for tokens */
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
	token_count = count_tokens(token, cp_input, delimiter);
	/* Allocate memory for tokens + 1 to NULL terminate the array */
	tokens = malloc(sizeof(char *) * (token_count + 1));
	if (tokens == NULL)
	{
		free(user_input);
		user_input = NULL;
		error_handling("malloc", EXIT_FAILURE);
	}
	/* Tokenize user input */
	token = strtok(user_input, delimiter);
	while (token)
	{
		tokens = tokenize_input(user_input, tokens, token, delimiter, i);
		i++;
	}
	/* Null terminate the array of pointer */
	tokens[i] = NULL;
	return (tokens);
}
