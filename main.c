#include "shell.h"

/**
 * display_prompt - Shows shell prompt with current directory
 */
void display_prompt(void)
{
	char cwd[BUFFER_SIZE];
	char *prompt = "$ ";

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s%s", cwd, prompt);

	fflush(stdout);
}

/**
 * exit_on_eof - Handles end of file (Ctrl + D)
 * @command_line: User input to free before exiting
 * @exit_status: Current exit status
 */
void exit_on_eof(char *command_line, int exit_status)
{
	printf("\n");
	free(command_line);
	if (exit_status != 0)
		exit(exit_status);
	exit(EXIT_SUCCESS);
}

/**
 * is_interactive - Checks if shell is in interactive mode
 * Return: 1 if interactive, 0 if not
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * main - Entry point of the shell program
 * @argc: Number of arguments (unused)
 * @argv: Array of arguments
 *
 * Return: Exit status of last command
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char *command_line = NULL;
	size_t buffer_size = 0;
	int chars_read = 0;
	int interactive_mode = 0;
	int exit_status = 0;

	while (1)
	{
		interactive_mode = is_interactive();
		if (interactive_mode)
			display_prompt();

		chars_read = getline(&command_line, &buffer_size, stdin);
		if (chars_read == -1)
			exit_on_eof(command_line, exit_status);

		exit_status = process_command(command_line, chars_read,
				environ, interactive_mode, argv, &exit_status);
	}

	free(command_line);
	return (0);
}
