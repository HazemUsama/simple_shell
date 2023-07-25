#include "shell.h"

/**
 * check_file - check if the file exist
 *
 * @path: the file path
 *
 * Return: the absolute path if exits otherwise NULL
 */
char *check_file(char *path)
{
	char *path_environ = getenv("PATH");
	char *env_cpy = strdup(path_environ);
	char *token, *new_path = NULL;
	size_t new_len;
	struct stat buffer;


	if (!path_environ)
		return (NULL);
	token = strtok(env_cpy, ":");

	while (token)
	{
		new_len = _strlen(token) + _strlen(path) + 2;
		new_path = malloc(new_len);
		if (new_path == NULL)
		{
			free(env_cpy);
			return (NULL);
		}
		strcpy(new_path, token);
		strcat(new_path, "/");
		strcat(new_path, path);
		strcat(new_path, "\0");
		if (!stat(new_path, &buffer))
		{
			free(env_cpy);
			return (new_path);
		}
		free(new_path);
		new_path = NULL;
		token = strtok(NULL, ":");
	}
	free(env_cpy);
	if (!stat(path, &buffer))
		return (strdup(path));
	return (NULL);
}
/**
 * exe_command - execute simple command
 *
 * @arguments: the command arguments
 *
 * Return: 0 on success 1 on failure
 */

int exe_command(char **arguments)
{
	char *command;
	int state;
	pid_t child;

	command = check_file(arguments[0]);
	if (command == NULL)
	{
		_putstr(arguments[0]);
		_putstr(": not found\n");
		return (1);
	}
	child = fork();

	if (child == -1)
	{
		perror("error: failed to fork\n");
		free(command);
		return (1);
	}
	if (!child)
	{
		execve(command, arguments, environ);
		perror("error: failed to execute command\n");
		_exit(1);
	}
	free(command);
	wait(&state);
	return (0);
}
/**
 * tokenize - split the line to multple strings
 *
 * Return: a pointer to the strings on success and NULL on failure
 */
char **tokenize(void)
{
	char *line = NULL, *token;
	char **arg = NULL;
	int argCount = 0, num_tokens = 0;

	readInput(&line);
	if (line[0] == '\0' || !strcmp(line, "\n"))
		return (NULL);

	num_tokens = countTokens(line, " \t\n");
	if (num_tokens == 1)
		return (NULL);
	arg = malloc(sizeof(char *) * num_tokens);
	if (arg == NULL)
	{
		perror("error: allocating arg\n");
		free(line);
		return (NULL);
	}
	token = strtok(line, " \t\n");
	while (token)
	{
		arg[argCount] = strdup(token);
		if (arg[argCount++] == NULL)
		{
			perror("error: allocating arg\n");
			freeArg(arg);
			free(line);
			return (NULL);
		}
		token = strtok(NULL, " \t\n");
	}
	arg[argCount] = NULL;
	free(line);
	return (arg);
}
