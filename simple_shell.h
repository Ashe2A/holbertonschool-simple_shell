#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/***** LIBRARIES *****/
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/***** CONSTANTS *****/
extern char **environ;
extern void _exit(int __status) __attribute__ ((__noreturn__));

/***************************** STRUCTURES *****************************/

/**
 * struct dir_s - node to store directory of PATH variable
 * @name: of the variable stored
 * @path: is the value stored in the variable
 * @next: is a pointer pointing to next node
 */
typedef struct dir_s
{
	char *name;
	char *path;
	struct dir_s *next;
} dir_t;

/**
 * struct built_in_s - is a library of functions associated to a command
 * @cmd: is the command line to call the function
 * @f: is the function call by cmd
 */
typedef struct built_in_s
{
	char *cmd;
	void (*f)(char *, char **, int);
} built_in_t;

/************************* FUNCTIONS *************************/
/* Main */
int initialize_mode_and_prompt(void);
void handle_eof_cleanup(int, char *, int);
int handle_user_command(char *, int, char **, int, char **, int*);

/* handle_user_command */
int check_and_run_builtin(char *, char **, int);
char **tokenize(char *);
char *path_parse(char *, char *);
pid_t fork_and_check(char **, char *, pid_t *, char *);
void execve_and_check(char **, char *, char **, char *);
void handle_command_not_found(int, char **, char **, char *);
void reset_ressources(char **, char *, int,	char *, int);

/* path_parse */
dir_t *build_path_list(dir_t **, char *, char *);
dir_t *create_node_at_end(dir_t **, char *, char *, char *);
void free_path_dir(dir_t *);

/* Built-ins */
void _printenv(char *, char **, int);
void _exit_function(char *, char **, int);

/* Helper functions */
void error_handling(char *, int);
char *_getenv(const char *);
void cleanup_tokens_and_path(char **, char *);
void child_error_handling(char *, int);
void free_tokens(char **);
int space_check(char *user_input);

#endif /* SIMPLE_SHELL_H */
