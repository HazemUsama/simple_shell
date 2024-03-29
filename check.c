#include "shell.h"
#include <stdlib.h>

/**
 * check_file - check if the file exist
 *
 * @path: the file path
 *
 * Return: the absolute path if exits otherwise NULL
 */
char *check_file(char *path)
{
	char *path_environ = _getenv("PATH");
	char *token, *new_path = NULL;
	size_t new_len;
	struct stat buffer;

	if (path_environ == NULL)
		return (_strdup(path));

	token = strtok(path_environ, ":");
	while (token)
	{
		new_len = _strlen(token) + _strlen(path) + 2;
		new_path = malloc(new_len);
		if (new_path == NULL)
		{
			free(path_environ);
			exit(EXIT_FAILURE);
		}
		strcpy(new_path, token);
		strcat(new_path, "/");
		strcat(new_path, path);
		strcat(new_path, "\0");

		if (!stat(new_path, &buffer) && buffer.st_mode & S_IXUSR)
		{
			free(path_environ);
			return (new_path);
		}
		free(new_path);
		new_path = NULL;
		token = strtok(NULL, ":");
	}
	free(path_environ);
	return (_strdup(path));
}
/**
 * exe_command - execute simple command
 *
 * @arguments: the command arguments
 * @program_name: ...
 * @count: ...
 *
 * Return: 0 on success -1 on failure
 */

int exe_command(char **arguments, char *program_name, int count)
{
	char *command, *prompt;
	int status, executable;
	pid_t child;

	if (checkBuild(arguments))
	{
		return (0);
	}

	command = check_file(arguments[0]);
	executable = check_exec(command);


	if (executable != 1)
	{
		if (!executable)
			prompt = "permission denied\n";
		else
			prompt = "not found\n";
		print_err(program_name, count, command, prompt);
		free(command);
		return (127);
	}
	child = fork();
	if (child == -1)
	{
		perror("error: failed to fork\n");
		free(command);
		return (-1);
	}
	if (!child)
	{
		if (execve(command, arguments, environ) == -1)
			perror("error: failed to execute command\n");
	}
	free(command);
	wait(&status);
	if (WIFEXITED(status))
		errno = WEXITSTATUS(status);
	return (0);
}
/**
 * tokenize - split the line to multple strings
 *
 * @size: the size of the environ before
 *
 * Return: a pointer to the strings on success and NULL on failure
 */
char **tokenize(int size)
{
	char *line, *token;
	char **arg = NULL;
	int argCount = 0, num_tokens = 0;

	line = readInput(size);
	if (checkEmpty(line))
	{
		free(line);
		return (NULL);
	}

	num_tokens = countTokens(line, " \t\n");
	if (num_tokens == 1)
	{
		free(line);
		return (NULL);
	}
	arg = malloc(sizeof(char *) * num_tokens);
	if (arg == NULL)
	{
		perror("error: allocating arg\n");
		free(line);
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " \t\n");
	while (token)
	{
		arg[argCount] = _strdup(token);
		if (arg[argCount++] == NULL)
		{
			perror("error: allocating arg\n");
			freeArg(arg);
			free(line);
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \t\n");
	}
	arg[argCount] = NULL;
	free(line);
	return (arg);
}
