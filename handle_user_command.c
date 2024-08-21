#include "simple_shell.h"

/**
 * space_check - check if the user input is empty after space
 * @user_input: command and arguments of the user input
 *
 * Return: 1 if command is found, 0 otherwise
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

/**
 * handle_user_command - parses an executes user's input command
 * @use_input: command and arguments of the user input
 * @read: number of characters of the user input (counted by getline())
 * @cpy_env: shell's environment variables
 * @is_interactive: 1 is interactive, 0 is not
 * @av: the command-line's arguments
 * @child_status: exit status of the program
 *
 * Return: the child's status, 0 if no error, another error code otherwise
 */
int handle_user_command(char *use_input, int read,
	char **cpy_env, int is_interactive, char **av, int *child_status)
{
	char **tokens = NULL; /* the extracted tokens */
	/* 0 if user input is a full path command, 1 (default) if not */
	int is_f_path = 1;
	char *full_path = NULL; /* the complete path of the user input command */
	pid_t child_pid = 0;  /* the child's process ID */
	int status;	/* ... of the child returned by wait() */

	/* Check empty command_input */
	if ((use_input[0] != '\n' && read != 1) && space_check(use_input) != 0)
	{
		/* Transforms user cmd into arg for execve */
		tokens = tokenize(use_input);
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
	child_status = 0; /* If no child doesn' t return error, reset to 0 */
	return (0);	/* No error encountered by the child */
}
