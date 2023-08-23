#ifndef SHELL_H
#define SHELL_H
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* functions(string) */
int custom_strlen(const char *str);
char *custom_strcat(char *destination, const char *source);
char *custom_strncat(char *destination, const char *source, size_t num);
char *custom_strcpy(char *destination, const char *source);
char *custom_strchr(char *str, char character);
int custom_strspn(char *str, char *characters);
int custom_strcmp(char *str1, char *str2);
int custom_strncmp(const char *str1, const char *str2, size_t num);


/* builtin command (built_in_command0.c */
int (*getBuiltin(char *command))(char **args, char **front);
int command_handler_exit(char **args, char **front);
int command_handler_env(char **args, char __attribute__((__unused__)) **front);
int command_handler_setenv(char **args, char __attribute__((__unused__)) **front);
int command_handler_unsetenv(char **args, char __attribute__((__unused__)) **front);
int command_handler_cd(char **args, char __attribute__((__unused__)) **front);
int command_handler_alias(char **args, char __attribute__((__unused__)) **front);
int command_handler_help(char **args, char __attribute__((__unused__)) **front);

/* buildin command environment(buildin_env)*/
char **copy_environ(void);
void free_environ(void);
char **get_environ_var(const char *var);


/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
char *dir;
struct list_s *next;
} list_tab;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
char *name;
int (*f)(char **argv, char **front);
} builtin_tab;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
char *name;
char *value;
struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* global environemnt */
extern char **env;
/* global name*/
char *name;  
/* global history*/
int hist;

/* input (helps)*/
void free_args(char **args, char **front);


/* Errors(Handling)*/
int create_error(char **args, int err);

/* linkedlist(help) */
void free_alias_list(alias_t *head);
void free_list(list_tab *head);

#endif /* SHELL_H */

