#include "simple_shell.h"

/**
 * handle_command_not_found - prints error message if the command is not found
 * @is_interactive: 1 for interactive mode and 0 for non-interactive
 * @av: is an array of pointers pointing arrays of string
 * @tokens: is an array of pointers to the extracted tokens
 *
 * Description: the error messages are differents,
 * if the shell is in interactive or non-interactive mode
 *
 * Return: Always nothing
 */
void handle_command_not_found(int is_interactive, char **av, char **tokens)
{
	if (is_interactive == 0)
		printf("%s: 1: %s: not found\n", av[0], tokens[0]);
	else
		printf("%s: command not found: %s\n", av[0], tokens[0]);
}
