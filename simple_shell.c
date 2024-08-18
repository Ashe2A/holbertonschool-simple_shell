#include "simple_shell.h"

/**
	* main - entry point of the program
	* @argc: is the number of command-line argument
	* @argv: is an array of pointers pointing arrays of strings
	* storing the command-line arguments
	*
	* Return: Always returns 0 (success)
	*/
int main(int argc __attribute__((unused)), char **argv)
{
	int is_interactive = 0; /* 0 is off, 1 is on on */
	int bytes_read = 0; /* Is the number of bytes bytes_read by getline */
	char *user_input = NULL; /* Buffer to store user input */
	size_t n = 0;	/* is the number of bytes allocated to user_input by getline */
	char **cp_env = environ; /* Create a copy to fully access to command */

	while (1)	/* Infinite loop for shell */
	{
		/* Display prompt and switch interactive mode */
		is_interactive = initialize_mode_and_prompt();

		/* Wait and store the user's input; manages CTRL + D */
		bytes_read = getline(&user_input, &n, stdin);
		handle_eof_cleanup(bytes_read, user_input);

		/* Parse and execute command */
		handle_user_command(user_input, bytes_read, cp_env, is_interactive, argv);
	}

	/* Cleanup memory */
	free(user_input);
}
