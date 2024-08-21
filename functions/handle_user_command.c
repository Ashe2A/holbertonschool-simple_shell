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
 * check_and_run_builtin - call built-in functions if it's one
 * @user_input: user input with the possible built-in
 * @tokens: tokenized user input
 * @child_status: exit code of the child process
 *
 * Return: 1 if it's a built-in, 0 otherwise
 */
int check_and_run_builtin(char *user_input, char **tokens, int child_status)
{
	/* Built-in functions and their corresponding calls */
	built_in_t built_in_list[] = {
		{"env", _printenv},
		{"exit", _exit_function},
		{NULL, NULL}
	};
	int i = 0;

	/* Compare user input with structure commands and run if found */
	while (built_in_list[i].cmd != NULL)
	{
		if (strcmp(tokens[0], built_in_list[i].cmd) == 0)
		{
			built_in_list[i].f(user_input, tokens, child_status);
			return (1); /* Built-in mode on */
		}
		i++;
	}

	return (0); /* Built-in mode off */
}

/**
 * handle_command_not_found - prints error message if the command is not found
 * @is_interactive: 1 for interactive mode and 0 for non-interactive
 * @av: the command-line's arguments (tokens ?)
 * @tokens: to free
 * @user_input: to free
 *
 * Description: the error messages are differents,
 * if the shell is in interactive or non-interactive mode
 */
void handle_command_not_found(int is_interactive, char **av,
	char **tokens, char *user_input)
{
	if (is_interactive == 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", av[0], EXIT_FAILURE, tokens[0]);
		/* Free after printing the message error */
		free(user_input);
		free_tokens(tokens);
		exit(127);
	}
	else
		perror(av[0]);
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
	int status = 0, is_f_path = 1; /* + status of the child written by waitpid() */
	char *full_path = NULL; /* the complete path of the user input command */
	pid_t child_pid = 0;  /* the child's process ID */

	/* Check empty command_input */
	if ((use_input[0] != '\n' && read != 1) && (space_check(use_input) != 0))
	{
		tokens = tokenize(use_input); /* Transforms user cmd into arg for execve */
		/* Built-in command check */
		if (check_and_run_builtin(use_input, tokens, *child_status) == 0)
		{
			is_f_path = access(tokens[0], X_OK); /* checks if command is with path */
			if (is_f_path == 0)
				full_path = tokens[0]; /* if command has path */
			else
				full_path = path_parse(tokens[0], use_input); /* if not search for path */
			if (full_path != NULL) /* If path exists, create child process */
			{
				child_pid = fork_and_check(tokens, full_path, &child_pid, use_input);
				if (child_pid == 0)	/* In the child process */
					execve_and_check(tokens, full_path, cpy_env, use_input);
				else /* In another (mostly parent) process */
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
