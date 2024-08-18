#include "simple_shell.h"

/**
 * child_error_handling - handles errors for a child process
 * @msg: is a string containing the error message to be printed
 * @exit_code: for the child process
 *
 * Description: This function prints an error message using `perror`
 * and exits the child process with the specified exit code. It uses
 * _exit that avoid interference with the parent like unnecessary clean-up.
 *
 * Return : Always void
 */
void child_error_handling(char *msg, int exit_code)
{
	perror(msg);
	/* Don't need a full clean to exit a child process */
	_exit(exit_code);
}
