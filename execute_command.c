#include "shell.h"

/**
 * execve_command - Executes a command using execve
 * @args: Command arguments
 * @path: Full path of command
 * @env: Environment variables
 * @command_line: Original command line
 */
void execve_command(char **args, char *path, char **env, char *command_line)
{
	if (execve(path, args, env) == -1)
	{
		free(command_line);
		clean_resources(args, path, 1, command_line, 0);
		display_error("execve", EXIT_FAILURE);
	}
}

/**
 * execute_command - Creates and executes child process
 * @args: Command arguments
 * @path: Full path of command
 * @child_pid: Pointer to child process ID
 * @command_line: Original command line
 * Return: Process ID of child
 */
pid_t execute_command(char **args, char *path, pid_t *child_pid,
		char *command_line)
{
	*child_pid = fork();

	if (*child_pid == -1)
	{
		free(command_line);
		clean_resources(args, path, 1, command_line, 0);
		display_error("fork", EXIT_FAILURE);
	}

	return (*child_pid);
}

/**
 * fork_and_execute - Forks process and executes command
 * @args: Command arguments
 * @path: Full path of command
 * @env: Environment variables
 * @command_line: Original command line
 * Return: Status of command execution
 */
int fork_and_execute(char **args, char *path, char **env, char *command_line)
{
	pid_t child_pid;
	int status = 0;

	child_pid = execute_command(args, path, &child_pid, command_line);

	if (child_pid == 0)
	{
		execve_command(args, path, env, command_line);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}

	return (status);
}
