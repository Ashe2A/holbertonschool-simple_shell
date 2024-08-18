#include "simple_shell.h"

/**
 * handle_eof_cleanup - to handle control + D
 * @read: is an integer that stores the number of bytes by getline
 * @user_input: is a string to free
 *
 * Return : Always nothing
 */
void handle_eof_cleanup(int read, char *user_input)
{
	int i = 0;

	/* Control + D */
	if (read == -1)
	{
		/* Memory clean up */
		free(user_input);
		while (custom_environ[i] != NULL)
		{
			free(custom_environ[i]);
			i++;
		}
		free(custom_environ);
		printf("\n");
		exit(0);
	}
}
