#include "simple_shell.h"

/**
	* change_directory - change the current directory
	* 
	* Return: Always nothing
	*/ 
void change_directory(char *user_input __attribute__((unused)), char **av)
{
	/* If no argument, go HOME */
	if (av[1] == NULL)
		chdir(_getenv("HOME"));

	/* If '-' argument, go to the last directory */
	if (strcmp(av[1], "'"))
		chdir(_getenv("OLDPWD"));

	chdir(av[1]);
}
