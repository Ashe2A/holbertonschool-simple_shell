#include "simple_shell.h"

void go_home(void);
void go_back(void);
void go_dir(char **tokens);

/**
	* change_directory - change the current directory
	* @user_input: unused
	* @tokens: is a string where is stored the next current directory
	*
	* Return: Always nothing
	*/
void change_directory(char *user_input __attribute__((unused)), char **tokens)
{
	/* Structure which would stores the metadata */
	struct stat sb;

	/* 'cd' is the only entry */
	if (tokens[1] == NULL)
		go_home();

	/* If '-' argument, go to the last directory */
	else if (strcmp(tokens[1], "-") == 0)
		go_back();

	/* Check is path to folder is valid */
	else if (stat(tokens[1], &sb) == 0)
		go_dir(tokens);

	else
		perror("");
}

/**
 * go_home - change the working directory to HOME
 *
 * Description: Change the working directory
 * to HOME and update OLDPWD and PWD
 *
 * Return: Always Nothing
 */
void go_home(void)
{
	/* Do not activate OLDPWD if you are already at HOME */
	if (strcmp(_getenv("PWD"), _getenv("HOME")) != 0)
		if (_setenv("OLDPWD", _getenv("PWD"), 1) == -1)
			error_handling("_setenv", EXIT_FAILURE);

	if (chdir(_getenv("HOME")) == -1)
		error_handling("chdir", EXIT_FAILURE);

	if (_setenv("PWD", _getenv("HOME"), 1) == -1)
		error_handling("_setenv", EXIT_FAILURE);
}

/**
 * go_back- change the working directory to OLDPWD
 *
 * Description: Change the working directory
 * to OLDPWD and update it, plus PWD
 *
 * Return: Always Nothing
 */
void go_back(void)
{
	/* Declares current working directory array */
	char cwd[PATH_MAX];

	if (chdir(_getenv("OLDPWD")) == -1)
		error_handling("chdir", EXIT_FAILURE);

	if (_setenv("OLDPWD", _getenv("PWD"), 1) == -1)
		error_handling("_setenv", EXIT_FAILURE);

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		error_handling("getcwd", EXIT_FAILURE);

	if (_setenv("PWD", cwd, 1) == -1)
		error_handling("_setenv", EXIT_FAILURE);
}

/**
 * go_dir - change the working directory to another
 * @tokens: is a string where is stored the next current directory
 *
 * Description: Change the working directory
 * to OLDPWD and update it, plus PWD
 *
 * Return: Always Nothing
 */
void go_dir(char **tokens)
{
	/* Declares current working directory array */
	char cwd[PATH_MAX];

	if (_setenv("OLDPWD", _getenv("PWD"), 1) == -1)
		error_handling("_setenv", EXIT_FAILURE);

	chdir(tokens[1]);

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		error_handling("getcwd", EXIT_FAILURE);

	if (_setenv("PWD", cwd, 1) == -1)
		error_handling("_setenv", EXIT_FAILURE);
}
