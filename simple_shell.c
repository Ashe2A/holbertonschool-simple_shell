#include "simple_shell.h"

/**
	* main - entry point
	* @ac: is the number of arguments
	* @av: is an array of pointers pointing arrays of string
	*
	* Return: (0)
	*/
int main(int ac __attribute__((unused)), char **av)
{
	int is_interactive = 0; /* 0 is off, 1 is on on */
	int read = 0; /* Is the number of bytes read by getline */
	char *user_input = NULL; /* Stored by getline */
	size_t n = 0;	/* is the number of bytes allocated to user_input by getline */
	char **cpy_env = environ;	/* is environment to export in the new shell */

	while (-1)
	{
		/* Display prompt and switch interactive mode */
		is_interactive = initialize_mode_and_prompt();

		/* Waits and stores the user's input and manages CTRL + D*/
		read = getline(&user_input, &n, stdin);
		handle_eof_cleanup(read, user_input);

		/* Parses and execute command */
		handle_user_command(user_input, read, cpy_env, is_interactive, av);
	}
	free(user_input);
}
