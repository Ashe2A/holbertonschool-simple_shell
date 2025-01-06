#include "shell.h"

/**
 * print_env - Prints current environment
 * @command_line: Command line (unused)
 * @args: Command arguments (unused)
 * @status: Exit status (unused)
 */
void print_env(char *command_line __attribute__((unused)),
		char **args __attribute__((unused)), int status)
{
	int i = 0;

	(void)status;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * shell_exit - Exits shell with given status
 * @command_line: Command line to free
 * @args: Command arguments
 * @status: Current exit status
 */
void shell_exit(char *command_line, char **args, int status)
{
	int exit_code = status;

	if (args[1])
	{
		exit_code = atoi(args[1]);
		if (exit_code < 0)
		{
			fprintf(stderr, "./hsh: exit: Illegal number: %s\n", args[1]);
			exit_code = 2;
		}
	}

	clean_command_array(args);
	free(command_line);
	exit(exit_code);
}

/**
 * execute_builtin - Executes builtin command if exists
 * @command_line: Original command line
 * @args: Command arguments
 * @status: Current exit status
 * Return: 1 if builtin executed, 0 if not
 */
int execute_builtin(char *command_line, char **args, int status)
{
	int i = 0;
	builtin_t builtins[] = {
		{"env", print_env},
		{"exit", shell_exit},
		{NULL, NULL}
	};

	if (!args || !args[0])
		return (0);

	while (builtins[i].name)
	{
		if (strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].f(command_line, args, status);
			return (1);
		}
		i++;
	}

	return (0);
}
