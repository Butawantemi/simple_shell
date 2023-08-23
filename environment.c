#include "shell.h"

char **copy_environ(void);
void free_environ(void);
char **get_environ_var(const char *var);

/**
 *copy_environ - create a copy of the environment.
 *
 * Return: if an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_environ(void)
{
char **newEnv;
size_t size;
int index;
for (size = 0; env[size]; size++)
		;
newEnv = malloc(sizeof(char *) * (size + 1));
if (!newEnv)
return (NULL);
for (index = 0; env[index]; index++)
{
newEnv[index] = malloc(custom_strlen(env[index]) + 1);
if (!newEnv[index])
{
for (index--; index >= 0; index--)
free(newEnv[index]);
free(newEnv);
return (NULL);
}
custom_strcpy(newEnv[index], env[index]);
}
newEnv[index] = NULL;
return (newEnv);
}

/**
 * Free_environ - frees the the environ copy.
 */
void free_environ(void)
{
int index;
for (index = 0; env[index]; index++)
free(env[index]);
free(env);
}

/**
 * get_environ_var - get an environmental variable from the path.
 * @var: the name of the environmental variable to get.
 *
 * Return: if the environmental variable does not exist, otherwise - a pointer to the environmental variable.
 */
char **get_environ_var(const char *var)
{
int index, len;
len = custom_strlen(var);
for (index = 0; env[index]; index++)
{
if (custom_strncmp(var, env[index], len) == 0)
return (&env[index]);
}
return (NULL);
}
