#include "shell.h"

/**
 * is_empty_line - Check if input is empty or only spaces
 * @command_line: Command line to check
 * @read_size: Size of the command line
 * Return: 1 if empty, 0 if not
 */
int is_empty_line(const char *command_line, int read_size)
{
	int i = 0;

	if (command_line[0] == '\n' && read_size == 1)
		return (1);

	while (command_line[i] == ' ' || command_line[i] == '\t')
	{
		if (command_line[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * prepare_command - Prepares command by splitting and checking builtins
 * @command_line: Command to prepare
 * @exit_status: Current exit status
 * Return: Array of arguments or NULL if builtin executed
 */
static char **prepare_command(char *command_line, int *exit_status)
{
	char **args = split_command(command_line);

	if (!args)
		return (NULL);

	if (execute_builtin(command_line, args, *exit_status))
	{
		clean_command_array(args);
		return (NULL);
	}
	return (args);
}

/**
 * find_command - Locates command in PATH or as full path
 * @args: Command arguments
 * @command_line: Original command line
 * @is_full_path: Pointer to full path flag
 * Return: Path to command or NULL if not found
 */
static char *find_command(char **args, char *command_line, int *is_full_path)
{
	*is_full_path = access(args[0], X_OK);
	if (*is_full_path == 0)
		return (args[0]);

	return (find_command_path(args[0], command_line));
}

/**
 * execute_child_process - Handles child process execution
 * @args: Command arguments
 * @full_path: Path to command
 * @env: Environment variables
 * @command_line: Original command line
 * Return: Process ID
 */
static pid_t execute_child_process(char **args, char *full_path,
		char **env, char *command_line)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		free(command_line);
		clean_resources(args, full_path, 1, command_line, 0);
		display_error("fork", EXIT_FAILURE);
	}

	if (child_pid == 0)
		execve_command(args, full_path, env, command_line);

	return (child_pid);
}

/**
 * process_command - Process and execute a command
 * @command_line: Command to process
 * @read_size: Size of command
 * @env: Environment variables
 * @is_interactive: Interactive mode flag
 * @program_args: Program arguments
 * @exit_status: Exit status pointer
 * Return: Command execution status
 */
int process_command(char *command_line, int read_size, char **env,
		int is_interactive, char **program_args, int *exit_status)
{
	char **args = NULL;
	char *full_path = NULL;
	pid_t child_pid;
	int status = 0, is_full_path = 1;

	if (is_empty_line(command_line, read_size))
		return (0);

	args = prepare_command(command_line, exit_status);
	if (!args)
		return (0);

	full_path = find_command(args, command_line, &is_full_path);
	if (full_path)
	{
		child_pid = execute_child_process(args, full_path, env, command_line);
		waitpid(child_pid, &status, 0);
	}
	else
		print_command_error(is_interactive, program_args, args, command_line);

	clean_resources(args, full_path, is_full_path, command_line, read_size);

	if (WIFEXITED(status))
	{
		*exit_status = WEXITSTATUS(status);
		return (*exit_status);
	}
	return (0);
}
