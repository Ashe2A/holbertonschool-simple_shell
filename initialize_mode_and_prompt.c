#include "hsh.h"

/**
 * initialize_mode_and_prompt - displays a prompt
 * and set the interactive mode
 *
 * Return: 1 for interactive mode and 0 for non-interactive
 */
int initialize_mode_and_prompt(void)
{
	/* Buffer for store the actual directory displayed in the prompt */
	char cwd[256];
	char *prompt = "$ "; /* Indicate that shell is ready to take input */
	int mode = 0;	/* Non-interactive by default */

	/* Check whether the command is being executed by another terminal */
	if (isatty(0))
	{
		mode = 1;	/* Switch to interactive */

		/* Display the prompt with actual working directory */
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("%s%s", cwd, prompt);

		/* Make sure that prompts are displayed before waiting for input */
		fflush(stdout);
	}

	return (mode);
}
