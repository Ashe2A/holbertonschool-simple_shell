#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/*****************LIBRARIES****************/

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*******************CONSTANTS*****************/

extern char **environ;

/*****************STRUCTURES***************/

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
	void (*f)(char *);
} built_in_t;

/*****************FUNCTIONS****************/
/* Main */
int initialize_mode_and_prompt(void);
void handle_eof_cleanup(int, char *);
void handle_user_command(char *, int, char **, int, char **);

/* handle_user_command */
int check_and_run_builtin(char *);
char **tokenize(char *);
char *path_parse(char *);
pid_t fork_and_check(char **tokens, char *full_path, pid_t *child_pid);
void execve_and_check(char **tokens, char *full_path, char **env);
void handle_command_not_found(int is_interactive, char **av, char **tokens);
void reset_ressources(char **tokens, char *full_path, int is_full_path,
						char *user_input, int read);

/* path_parse */
dir_t *build_path_list(dir_t **, char *);
dir_t *create_node(dir_t **head, char *name, char *value);
void free_path_dir(dir_t *head);
pid_t fork_and_check(char **tokens, char *full_path, pid_t *child_pid);

/* Built-in */
void _printenv(char *user_input __attribute__((unused)));

/* Helper functions */
void error_handling(char *msg, int exit_code);
char *_getenv(const char *name);
void cleanup_tokens_and_path(char **tokens, char *full_path);
void child_error_handling(char *msg, int exit_code);
void free_tokens(char **tokens);


#endif /* SIMPLE_SHELL_H */
