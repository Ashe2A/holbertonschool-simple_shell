#include "simple_shell.h"

/**
 * handle_eof_cleanup - to handle control + D
 * @read: is an integer that stores the number of bytes by getline
 * @user_input: is a string to free
 * @child_status: is in an integer storing the return value of a child
 *
 * Return : Always nothing
 */
void handle_eof_cleanup(int read, char *user_input, int child_status)
{
	/* Control + D */
	if (read == -1)
	{
		/* Memory clean up */
		free(user_input);
		user_input = NULL;

		/* Return the exit code of the child if its encountered errors */
		if (child_status != 0)
			exit(child_status);

		exit(EXIT_SUCCESS);
	}
}
