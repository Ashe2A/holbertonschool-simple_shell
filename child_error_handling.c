#include "hsh.h"

/**
 * child_error_handling - is used to handle
 * execution failures of a child process
 * @msg: is a string stroring the error message
 * @exit_code: to indicate
 *
 * Return : Always nothing
 */
void child_error_handling(char *msg, int exit_code)
{
	perror(msg);
	/* Don't need a full clean to exit a child process */
	_exit(exit_code);
}
