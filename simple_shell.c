#include "simple_shell.h"

char **custom_environ = NULL;

/**
	* main - entry point
	* @argc: is the number of arguments
	* @argv: is an array of pointers pointing arrays of string
	*
	* Return: (0)
	*/
int main(int argc __attribute__((unused)), char **argv)
{
	int is_interactive = 0; /* 0 is off, 1 is on on */
	int read = 0; /* Is the number of bytes read by getline */
	char *user_input = NULL; /* Stored by getline */
	size_t n = 0;	/* is the number of bytes allocated to user_input by getline */
	int i = 0;

	/* Create of full malloc'ed  environment*/
	custom_environ = create_custom_environ();

	/* Shell main loop */
	while (-1)
	{
		/* Display prompt and switch interactive mode */
		is_interactive = initialize_mode_and_prompt();

		/* Waits and stores the user's input and handle CTRL + D*/
		read = getline(&user_input, &n, stdin);
		handle_eof_cleanup(read, user_input);

		/* Parses and execute command */
		handle_user_command(user_input, read, is_interactive, argv);
	}
	free(user_input);

	while (custom_environ[i] != NULL)
	{
		free(custom_environ[i]);
		i++;
	}
	free(custom_environ);

	return (0);
}
