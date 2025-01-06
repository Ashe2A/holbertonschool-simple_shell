#include "shell.h"

/**
 * display_error - Displays error message and exits program
 * @msg: Error message to display
 * @exit_code: Exit status code
 */
void display_error(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}

/**
 * print_command_error - Prints command not found error
 * @is_interactive: Shell mode (1 interactive, 0 non-interactive)
 * @program_args: Program arguments
 * @args: Command arguments to free
 * @command_line: Command line to free
 */
void print_command_error(int is_interactive, char **program_args,
		char **args, char *command_line)
{
	cleanup_t *cleanup_data;
	char *prog_name = program_args[0];
	char *cmd = args[0];

	if (!is_interactive)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name,
				EXIT_FAILURE, cmd);
		cleanup_data = create_cleanup_info(command_line, args, NULL);
		if (cleanup_data)
		{
			free(cleanup_data);
			exit(127);
		}
	}
	else
		perror(prog_name);
}

/**
 * create_cleanup_info - Creates cleanup info structure
 * @command_line: Command line to store
 * @args: Arguments array to store
 * @path: Command path to store
 * Return: Pointer to cleanup_info structure
 */
cleanup_t *create_cleanup_info(char *command_line, char **args, char *path)
{
	cleanup_t *info = malloc(sizeof(cleanup_t));

	if (!info)
		return (NULL);

	info->command_line = command_line;
	info->args = args;
	info->path = path;

	return (info);
}
