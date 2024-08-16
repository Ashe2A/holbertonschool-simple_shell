#include "simple_shell.h"

/**
 * error_handling - prints error's message and exit the shell
 * @msg: to display when an error occurs
 * @exit_code: to precise. 0 for success or others numbers for failure
 *
 * Return _ Always nothing
 */
void error_handling(char *msg, int exit_code)
{
	perror(msg);
	exit(exit_code);
}
