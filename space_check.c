#include "simple_shell.h"

/**
 * input_space_check - check if the user input is empty after space
 * @user_input: is a string storing the command of the user
 *
 * Return: 1 if command is find, otherwise 0
 */
int space_check(char *user_input)
{
	/* Traverse user's input */
	while (*user_input == ' ')
	{
		/* If rhe carriage return if found, there is no command to parse */
		if (*(user_input + 1) == '\n')
			return (0);

		user_input++;
	}
	return (1);
}
