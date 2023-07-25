#include "shell.h"

/**
* main - simpe shell program
*
* @argc: number of arguments
* @argv: the arguments
* @env: the enviroment
*
* Return: 0 on success and 1 in failer
*/


int main(notUsed int argc, notUsed char **argv, char **env)
{
	char **arg = NULL;

	environ = env;
	while (1)
	{
		promt();
		arg = tokenize();
		if (arg == NULL)
			continue;

		exe_command(arg);
		freeArg(arg);
	}
	return (0);
}
