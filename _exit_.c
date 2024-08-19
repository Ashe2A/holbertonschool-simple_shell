#include "simple_shell.h"

/**
 * _exit_ - clean the system and exit the porgram
 * @status: returned to the parent
 *
 * Return: Always void
 */
void _exit_(int status)
{
	exit(status);
}
