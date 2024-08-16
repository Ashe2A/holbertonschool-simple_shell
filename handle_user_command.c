#include "simple_shell.h"

/**
 * handle_user_command - parses an executes user's input command
 * @user_input: is a string. that stores the command given by the user
 * @read: is an integer that stores the number of bytes read by getline()
 * @cpy_env: is double array that contains
 * all environment variable of the shell
 * @is_interactive: 1 for interactive mode and 0 for non-interactive
 * @av: is an array of pointers pointing arrays of string
 *
 * Return: Always nothing
 */
void handle_user_command(char *user_input, int read,
char **cpy_env, int is_interactive, char **av)
{
	char **tokens = NULL; /* Is an array of pointers to the extracted tokens */
	int is_full_path = 1; /* 0 if user enter a command with full path */
	char *full_path = NULL; /* is the complete path of user's input */
	pid_t child_pid = 0;  /* is an ID of the child */
	int status;	/* of the child used by wait() */

	/* Check empty command_input an Built-in command check */
		if ((user_input[0] != '\n' && read != 1) &&
		check_and_run_builtin(user_input, av) == 0)
		{
			tokens = tokenize(user_input);	/* Transforms user cmd into arg for execve */
			/* Cmd is entered with its path or alone */
			is_full_path = access(tokens[0], X_OK);
			full_path = (is_full_path == 0) ? tokens[0] : path_parse(tokens[0]);

			if (full_path != NULL)
			{	/* Create a child process */
				child_pid = fork_and_check(tokens, full_path, &child_pid);
				if (child_pid == 0)	/* In the child process */
					execve_and_check(tokens, full_path, cpy_env);
				else	/* in the parent process */
					wait(&status);
			}
			else
				/* Adapts the cmd not found msg if interactive mode is enabled or not. */
				handle_command_not_found(is_interactive, av, tokens);
		}
		/* Free all allocated memory */
		reset_ressources(tokens, full_path, is_full_path, user_input, read);
}
