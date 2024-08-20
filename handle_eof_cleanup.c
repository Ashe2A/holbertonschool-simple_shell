#include "simple_shell.h"

/**
 * handle_eof_cleanup - to handle control + D
 * @read: is an integer that stores the number of bytes by getline
 * @user_input: is a string to free
 * @status_child:
 *
 * Return : Always nothing
 */
void handle_eof_cleanup(int read, char *user_input, int status_child)
{
	/* Control + D */
	if (read == -1)
	{
		/* Memory clean up */
		free(user_input);
		user_input = NULL;

		if (status_child > 0)
			exit(status_child);

		exit(EXIT_SUCCESS);
	}
}
