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
 * promt - display '$' promt for the user
 *
 * Return: 0 when the input from the terminal else 1
 */
int promt(void)
{
	if (!isatty(fileno(stdin)))
		return (1);

	_putstr("$ ");
	return (0);
}

/**
 * readInput - read input from the terminal
 *
 * @line: where to store the input
 */
void readInput(char **line)
{
	size_t len = 0;
	ssize_t read;

	read = getline(&(*line), &len, stdin);
	if (read == EOF || !strcmp(*line, "exit\n"))
	{
		free(*line);
		exit(0);
	}
}

