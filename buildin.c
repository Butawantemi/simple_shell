#include "shell.h"

int (*getBuiltin(char *command))(char **args, char **front);
int command_handler_exit(char **args, char **front);
int command_handler_cd(char **args, char __attribute__((__unused__)) **front);
int command_handler_help(char **args, char __attribute__((__unused__)) **front);

/**
 * getBuiltin - matches a command with a corresponding command_handler builtin function.
 * @command: The command to match.
 *
 * Return: a function pointer to the corresponding builtin.
 */
int (*getBuiltin(char *command))(char **args, char **front)
{
builtin_tab funcs[] = {
{ "exit", command_handler_exit },
{ "env", command_handler_env },
{ "setenv", command_handler_setenv },
{ "unsetenv", command_handler_unsetenv },
{ "cd", command_handler_cd },
{ "alias", command_handler_alias },
{ "help", command_handler_help },
{ NULL, NULL }
};
int a;
for (a = 0; funcs[a].name; a++)
{
if (custom_strcmp(funcs[a].name, command) == 0)
break;
}
return (funcs[a].f);
}

/**
 * command_handler_exit - causes normal process termination for the command_handler shell.
 * @args: an array of arguments containing the exit value.
 * @front: a double pointer to the beginning of args.
 * Return: if there are no arguments - -3,if the given exit value is invalid - 2 and o/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int command_handler_exit(char **args, char **front)
{
int a, max_digits = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);
if (args[0])
{
if (args[0][0] == '+')
{
a = 1;
max_digits++;
}
for (; args[0][a]; a++)
{
if (a <= max_digits && args[0][a] >= '0' && args[0][a] <= '9')
num = (num * 10) + (args[0][a] - '0');
else
return (create_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (create_error(--args, 2));
args -= 1;
free_args(args, front);
free_environ();
free_alias_list(aliases);
exit(num);
}



