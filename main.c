#include "shell.h"

void sig_handler(int sig);

int execute_command(char **args, char **front);
/**
 * signal_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void signal_handler(int sig)
{
char *new_prompt = "\n$ ";
(void)sig;
signal(SIGINT, signal_handler);
write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute_command - execute a command in a process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
 int execute_command(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];

if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = find_location(command);
}

if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (create_error(args, 126));
else
ret = (create_error(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
execve(command, args, env);
if (errno == EACCES)
ret = (create_error(args, 126));
free_environ();
free_args(args, front);
free_alias_list(aliases);
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
int ret = 0, retn;
int *execution_result = &retn;
char *prompt = "$ ", *new_line = "\n";

name = argv[0];
hist = 1;
aliases = NULL;
signal(SIGINT, signal_handler);
*execution_result = 0;
env = copy_environ();
if (!env)
exit(-100);
if (argc != 1)
{
ret = process_file_commands(argv[1], execution_result);
free_environ();
free_alias_list(aliases);
return (*execution_result);
}
if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handle_args(execution_result);
free_environ();
free_alias_list(aliases);
return (*execution_result);
}
while (1)
{
write(STDOUT_FILENO, prompt, 2);
ret = handle_args(execution_result);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 1);
free_environ();
free_alias_list(aliases);
exit(*execution_result);
}
}

free_environ();
free_alias_list(aliases);
return (*execution_result);
}
