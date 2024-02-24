#include "shell.h"
#include <stdlib.h>

/**
 * freeArg - free the memory of args
 *
 * @args: a pointer to string
 */

void freeArg(char **args)
{
	size_t i;

	if (args == NULL)
		return;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}

	free(args);
}
/**
 * prompt - display '$' promt for the user
 *
 * Return: 1 when interactive else 0
 */
int prompt(void)
{
	if (!isatty(fileno(stdin)))
		return (0);

	_putstr("$ ");
	return (1);
}

/**
 * readInput - read input from the terminal
 *
 * @size: the size of the environ before
 * Return: the input
 */
char *readInput(int size)
{
	size_t len = 0;
	char *line = NULL;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == EOF)
	{
		free(line);
		while (environ[size])
		{
			free(environ[size]);
			environ[size++] = NULL;
		}

		exit(EXIT_SUCCESS);
	}
	return (line);
}

/**
 * check_exec - check if the file exist & executable
 *
 * @file: the file path
 *
 * Return: 1 if it exist and executable
 * 0 if exist but not executable
 * -1 if it doesn't exist
 */
int check_exec(char *file)
{
	struct stat sb;
	int slash = 0, i = 0;

	while (file[i])
	{
		if (file[i] == '/')
		{
			slash = 1;
			break;
		}
		i++;
	}
	if (!stat(file, &sb) && sb.st_mode & S_IXUSR && slash)
		return (1);
	else if (!stat(file, &sb) && slash)
		return (0);
	return (-1);
}

