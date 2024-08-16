#include "simple_shell.h"

/**
	* change_directory - change the current directory
	* @user_input: unused
	* @argv: is an array of pointers stored arguments
	*
	* Return: Always nothing
	*/
void change_directory(char *user_input __attribute__((unused)), char **argv)
{
	/* If no argument, go HOME */
	if (argv[1] == NULL)
		chdir(_getenv("HOME"));

	/* If '-' argument, go to the last directory */
	if (strcmp(argv[1], "'"))
		chdir(_getenv("OLDPWD"));

	chdir(argv[1]);
}
