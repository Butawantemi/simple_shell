#include "shell.h"

int command_handler_env(char **args, char __attribute__((__unused__)) **front);
int command_handler_setenv(char **args, char __attribute__((__unused__)) **front);
int command_handler_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * command_handler_env - prints the current environment.
 * @args: an array of arguments passed to the shell.
 * @front: a double pointer to the beginning of args.
 *
 * Return: if an error occurs - -1, Otherwise - 0.
 *
 * description: prints one variable per line.             
 */
int command_handler_env(char **args, char __attribute__((__unused__)) **front)
{
int index;
char nc = '\n';
if (!env)
return (-1);
for (index = 0; env[index]; index++)
{
write(STDOUT_FILENO, env[index], custom_strlen(env[index]));
write(STDOUT_FILENO, &nc, 1);
}
(void)args;
return (0);
}

/**
 * command_handler_setenv - changes or adds an environmental variable to the PATH.
 * @args: an array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * description: args[1] is the name of the new or existing path variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: if an error occurs - -1, Otherwise - 0.
 */
int command_handler_setenv(char **args, char __attribute__((__unused__)) **front)
{
char **env_var = NULL, **newEnv, *new_value;
size_t size;
int index;
if (!args[0] || !args[1])
return (create_error(args, -1));
new_value = malloc(custom_strlen(args[0]) + 1 + custom_strlen(args[1]) + 1);
if (!new_value)
return (create_error(args, -1));
custom_strcpy(new_value, args[0]);
custom_strcat(new_value, "=");
custom_strcat(new_value, args[1]);
env_var = get_environ_var(args[0]);
if (env_var)
{
free(*env_var);
*env_var = new_value;
return (0);
}
for (size = 0; env[size]; size++)
;
newEnv = malloc(sizeof(char *) * (size + 2));
if (!newEnv)
{
free(newEnv);
return (create_error(args, -1));
}
for (index = 0; env[index]; index++)
newEnv[index] = env[index];
free(env);
env = newEnv;
env[index] = new_value;
env[index + 1] = NULL;
return (0);
}

/**
 * command_handler_unsetenv - del an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1, otherwise - 0.
 */
int command_handler_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
char **env_var, **newEnv;
size_t size;
int index, index2;
if (!args[0])
return (create_error(args, -1));
env_var = get_environ_var(args[0]);
if (!env_var)
return (0);
for (size = 0; env[size]; size++)
;
newEnv = malloc(sizeof(char *) * size);
if (!newEnv)
return (create_error(args, -1));
for (index = 0, index2 = 0; env[index]; index++)
{
if (*env_var == env[index])
{
free(*env_var);
continue;
}
newEnv[index2] = env[index];
index2++;
}
free(env);
env = newEnv;
env[size - 1] = NULL;
return (0);
}
