#include "simple_shell.h"
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
	int i = 0;
	char *cp_input = NULL;	/* Create a copy to count number of tokens */

	/* Copy user_ input and error hanling */
	cp_input = strdup(user_input);
	if(cp_input == NULL)
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
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			while (tokens[i])
				free(tokens[--i]);
			free(tokens);
			free(user_input);
			error_handling("tokens", 1);
		}
		i++;
		token = strtok(NULL, delimiter);
	}

	/* Null terminate the array of pointer */
	tokens[i] = NULL;

	return (tokens);
}
