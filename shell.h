#ifndef SHELL_H
#define SHELL_H

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Global variables */
extern char **environ;

/* Constants */
#define MAX_TOKENS 100
#define BUFFER_SIZE 1024

/**
 * struct cleanup_info - Structure for memory cleanup
 * @command_line: Original command line
 * @args: Array of arguments
 * @path: Full path of command
 */
struct cleanup_info
{
	char *command_line;
	char **args;
	char *path;
};

typedef struct cleanup_info cleanup_t;

/**
 * struct builtin - Structure for builtin commands
 * @name: Command name
 * @f: Associated function
 */
struct builtin
{
	char *name;
	void (*f)(char *, char **, int);
};

typedef struct builtin builtin_t;

/* Main function prototypes */
int process_command(char *command_line, int read_size, char **env,
		int is_interactive, char **program_args, int *exit_status);
void execve_command(char **args, char *path, char **env, char *command_line);
char **split_command(char *command_line);
void clean_command_array(char **args);
char *find_command_path(char *command, char *command_line);

/* Built-in command prototypes */
void print_env(char *command_line, char **args, int status);
void shell_exit(char *command_line, char **args, int status);
int execute_builtin(char *command_line, char **args, int status);

/* Error handling prototypes */
void display_error(char *msg, int exit_code);
void print_command_error(int is_interactive, char **program_args,
		char **args, char *command_line);
cleanup_t *create_cleanup_info(char *command_line, char **args, char *path);

/* Memory management prototypes */
void clean_resources(char **args, char *path,
		int is_full_path, char *command_line, int read_size);
void *safe_malloc(size_t size, cleanup_t *cleanup);
char *safe_strdup(const char *str, cleanup_t *cleanup);
int is_empty_line(const char *line, int read_size);

/* Process handling prototypes */
void exit_on_eof(char *command_line, int exit_status);
int is_interactive(void);
void display_prompt(void);

#endif
