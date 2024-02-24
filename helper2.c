#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory.
 *
 * @str: the source string
 *
 * Return: returns a pointer to the duplicated string.
 * It returns NULL if insufficient memory was available
 */
char *_strdup(char *str)
{
	char *copy;
	int i, size = 0;

	if (str == NULL)
		return (NULL);

	while (str[size] != '\0')
		size++;

	copy = (char *)malloc((sizeof(char) * size) + 1);
	if (copy == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		copy[i] = str[i];
	copy[size] = '\0';

	return (copy);
}

/**
 * builtin_exit - ...
 *
 * @arg: the input
 * @program_name: ...
 * @err: errno
 * @count: ...
 *
 */
void builtin_exit(char **arg, char *program_name, int err, int count)
{
	if (arg[1])
	{
		if (!is_num(arg[1]))
		{
			errno = err = 2;
			print_err(program_name, count, arg[0], "Illegal number: ");
			_putstr(arg[1]), _putchar('\n');
			freeArg(arg);
			exit(2);
		}
		err = strToint(arg[1]);
	}
	freeArg(arg);
	exit(err);
}

/**
 * checkEmpty - ...
 * @line: the input
 *
 * Return: 1 if it is empty, meaning no commands
 * or arguments and only blank spaces, 0 otherwise
 */
int checkEmpty(char *line)
{
	int i;

	if (line[0] == '\0' || _strcmp(line, "\n") == 0)
		return (1);

	for (i = 0; line[i]; i++)
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);

	return (1);
}

/**
* checkBuild - check if it's a build in function
*
* arguments: the arguments
*
* return 1 if it's 0 otherwise
*/
int checkBuild(char **args)
{
	buildin buildins[] = {
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};
	size_t i = 0;

	while (buildins[i].name)
	{
		if (!_strcmp(buildins[i].name, args[0]))
		{
			buildins[i].func(args);
			return (1);
		}
		i++;
	}

	return (0);
}
