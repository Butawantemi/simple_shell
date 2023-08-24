#include "shell.h"

int nLen(int n);
char *a_toi(int n);
int createError(char **args, int err);

/**
 * nLen - Counts the digit length of a number.
 * @n: The number to measure.
 *
 * Return: The digit length.
 */
int nLen(int n)
{
unsigned int n1;
int len = 1;

if (n < 0)
{
len++;
n1 = n * -1;
}
else
{
n1 = n;
}
while (n1 > 9)
{
len++;
n1 /= 10;
}

return (len);
}

/**
 * a_toi - converts an integer to a string.
 * @n: The integer.
 *
 * Return: The converted string.
 */
char *a_toi(int n)
{
char *buffer;
int len = nLen(n);
unsigned int n1;

buffer = malloc(sizeof(char) * (len + 1));
if (!buffer)
return (NULL);

buffer[len] = '\0';

if (n < 0)
{
n1 = n * -1;
buffer[0] = '-';
}
else
{
n1 = n;
}

len--;
do {
buffer[len] = (n1 % 10) + '0';
n1 /= 10;
len--;
} while (n1 > 0);

 return (buffer);
}


/**
 * createError - writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int createError(char **args, int err)
{
char *error;

switch (err)
{
case -1:
error = error_env(args);
break;
case 1:
error = error_1(args);
break;
case 2:
if (*(args[0]) == 'e')
error = error_2_exit(++args);
else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
error = error_2_syntax(args);
else
error = error_2_cd(args);
break;
case 126:
error = error_126(args);
break;
case 127:
error = error_127(args);
break;
}
write(STDERR_FILENO, error, custom_strlen(error));

if (error)
free(error);
return (err);

}
