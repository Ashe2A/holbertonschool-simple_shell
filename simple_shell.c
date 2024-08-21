#include "simple_shell.h"

/**
 * initialize_mode_and_prompt - displays a prompt if interactive
 *
 * Return: 1 if interactive, 0 if not
 */
int initialize_mode_and_prompt(void)
{
	/* Buffer to store the current directory to be displayed in the prompt */
	char cwd[256];
	char *prompt = "$ "; /* Indicates that shell is ready to take input */
	int mode = 0; /* 1 is interactive, 0 (default) is not */

	/* Check whether the command is being executed by another terminal */
	if (isatty(0))
	{
		mode = 1;	/* Switch to interactive */

		/* Display the prompt with actual working directory */
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s%s", cwd, prompt);

		/* Make sure that prompts are displayed before waiting for input */
		fflush(stdout);
	}

	return (mode);
}

/**
 * handle_eof_cleanup - to handle end of file (Ctrl + D)
 * @read: number of characters of the user input (counted by getline)
 * @user_input: user's input to free upon exiting
 * @child_status: is in an integer storing the return value of a child
 */
void handle_eof_cleanup(int read, char *user_input, int child_status)
{
	/* Ctrl + D */
	if (read == -1)
	{
		/* Memory clean up */
		free(user_input);
		user_input = NULL;

		/* Return the child's exit code if any error was encountered */
		if (child_status != 0)
			exit(child_status);
		exit(EXIT_SUCCESS);
	}
}

/**
 * main - entry point of the program
 * @argc: number of the command-line's arguments (unused)
 * @argv: the command-line's arguments
 *
 * Return: Always 0 (SUCCESS)
 */
int main(int argc __attribute__((unused)), char **argv)
{
	int is_interactive = 0; /* 1 is interactive, 0 (default) is not */
	int bytes_read = 0; /* number of bytes read by getline */
	char *user_input = NULL; /* Buffer to store user input */
	size_t n = 0; /* number of bytes allocated to the user input by getline */
	int child_status = 0;

	while (1) /* Infinite loop for shell */
	{
		/* If interactive, switch to that mode and display prompt */
		is_interactive = initialize_mode_and_prompt();

		/* Wait for and store user input; also managing Ctrl + D */
		bytes_read = getline(&user_input, &n, stdin);
		handle_eof_cleanup(bytes_read, user_input, child_status);

		/* Parse and execute command */
		child_status = handle_user_command(user_input, bytes_read,
			environ, is_interactive, argv, &child_status);
	}

	/* Cleanup memory when ending the process */
	free(user_input);

	return (0);
}
