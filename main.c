#include "shell.h"
#include <stdlib.h>

/**
* main - simpe shell program
*
* @argc: number of arguments
* @argv: the arguments
*
* Return: 0 on success and other on failer
*/


int main(notUsed int argc, char **argv)
{
	char **arg = NULL;
	int exit_stat, count = 0, isPipe, err = 0;

	while (++count)
	{
		isPipe = prompt();
		arg = tokenize();
		if (arg == NULL)
			continue;

		if (!_strcmp(arg[0], "exit") && !isPipe)
			builtin_exit(arg, argv[0], err, count);

		exit_stat = exe_command(arg, argv[0], count);
		err = errno;
		freeArg(arg);
		if (exit_stat == -1)
			exit(EXIT_FAILURE);
		else if (exit_stat == 127 && !isPipe)
			exit(exit_stat);
	}
	return (0);
}
