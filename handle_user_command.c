#include "simple_shell.h"

/**
 * handle_user_command - parses an executes user's input command
 * @use_input: is a string. that stores the command given by the user
 * @read: is an integer that stores the number of bytes read by getline()
 * @cpy_env: is double array that contains
 * all environment variable of the shell
 * @is_interactive: 1 for interactive mode and 0 for non-interactive
 * @av: is an array of pointers pointing arrays of string
 * @child_status: is the integer that return its exit status
 *
 * Return: the child status, 0 if no error, otherwise an other error code
 */
int handle_user_command(char *use_input, int read,
char **cpy_env, int is_interactive, char **av, int *child_status)
{
	char **tokens = NULL; /* Is an array of pointers to the extracted tokens */
	int is_f_path = 1; /* 0 if user enter a command with full path */
	char *full_path = NULL; /* is the complete path of user's input */
	pid_t child_pid = 0;  /* is an ID of the child */
	int status;	/* of the child used by wait() */

	/* Check empty command_input */
	if ((use_input[0] != '\n' && read != 1) && space_check(use_input) != 0)
	{
		tokens = tokenize(use_input);	/* Transforms user cmd into arg for execve */

		/* Built-in command check */
		if (check_and_run_builtin(use_input, tokens, *child_status) == 0)
		{	/* Cmd is entered with its path or alone */
			is_f_path = access(tokens[0], X_OK);
			full_path = (is_f_path == 0) ? tokens[0] : path_parse(tokens[0], use_input);
			if (full_path != NULL)
			{
				/* Create a child process */
				child_pid = fork_and_check(tokens, full_path, &child_pid, use_input);
				if (child_pid == 0)	/* In the child process */
					execve_and_check(tokens, full_path, cpy_env, use_input);
				else	/* in the parent process */
					waitpid(child_pid, &status, 0);
			}
			else
				/* Adapts the cmd not found msg if interactive mode is enabled or not. */
				handle_command_not_found(is_interactive, av, tokens, use_input);
		}
	}
	/* Free all allocated memory */
	reset_ressources(tokens, full_path, is_f_path, use_input, read);

	if (WIFEXITED(status) != 0)	/* Child encountered an error ? */
	{
		*child_status = WEXITSTATUS(status);
		return (*child_status);	/* Return error code */
	}
	return (0);	/* No error encountered by the child */
}
