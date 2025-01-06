#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Buffer sizes */
#define MAX_TOKENS 100
#define PATH_MAX_LENGTH 4096
#define COMMAND_MAX_LENGTH 1024
#define PROMPT_MAX_LENGTH 256

/* Exit codes */
#define EXIT_COMMAND_NOT_FOUND 127
#define EXIT_EXEC_FAILED 126
#define EXIT_FORK_FAILED 1
#define EXIT_INVALID_ARG 2

/* Command delimiters */
#define COMMAND_DELIMITERS " \t\r\n"
#define PATH_DELIMITER ":"

/* Environment variables */
#define ENV_PATH "PATH"
#define ENV_HOME "HOME"

/* Error messages */
#define ERR_MALLOC "Memory allocation failed"
#define ERR_FORK "Fork failed"
#define ERR_EXEC "Command execution failed"
#define ERR_PATH "Path not found"
#define ERR_CMD_NOT_FOUND "Command not found"
#define ERR_INVALID_ARG "Invalid argument"

/* Prompt */
#define SHELL_PROMPT "$ "

/* Boolean values */
#define TRUE 1
#define FALSE 0

/* Special characters */
#define NEWLINE '\n'
#define SPACE ' '
#define TAB '\t'
#define NULL_CHAR '\0'

#endif
