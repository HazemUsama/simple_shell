#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * _setenv - Initialize a new environment variable, or modify an existing one
 *
 * @args: the arguments
 */
void _setenv(char **args)
{

	int i = 0, j, k, equal;
	char *key, *value;

	if (!args[1] || !args[2])
	{
		perror("error: missing arguments\n");
		return;
	}
	key = args[1];
	value = args[2];
	while (environ[i])
	{
		equal = 1;
		for (j = 0; environ[i][j] != '=' && key[j]; j++)
			if (key[j] != environ[i][j])
				equal = 0;
		if (equal && environ[i][j] == '=' && key[j] == '\0')
		{
			j++;
			for (k = 0; value[k] != '\0'; k++, j++)
				environ[i][j] = value[k];
			environ[i][j] = '\0';
			break;
		}
		i++;
	}
	if (!environ[i])
	{
		environ[i] = malloc(strlen(key) + strlen(value) + 2);
		if (!environ[i])
			exit(EXIT_FAILURE);
		strcpy(environ[i], key);
		strcat(environ[i], "=");
		strcat(environ[i], value);
		strcat(environ[i], "\0");
		environ[i + 1] = NULL;

	}
}

/**
 * _unsetenv - Remove an environment variable
 *
 * @args: the arguments
 */
void _unsetenv(char **args)
{
	int i = 0, j, equal;
	char *key;

	if (!args[1])
	{
		perror("error: missing arguments\n");
		return;
	}
	key = args[1];

	while (environ[i])
	{
		equal = 1;
		for (j = 0; environ[i][j] != '=' && key[j]; j++)
			if (key[j] != environ[i][j])
				equal = 0;
		if (equal && environ[i][j] == '=' && key[j] == '\0')
		{
			free(environ[i]);
			environ[i] = environ[i + 1];
			while (environ[i])
			{
				i++;
				environ[i] = environ[i + 1];
			}
			return;
		}
		i++;
	}
}
/**
* env - print the environment variables
*
* @args: the arguments
*/
void env(notUsed char **args)
{
	size_t i = 0;

	while (environ[i])
	{
		_putstrout(environ[i++]);
		_putcharout('\n');
	}
}
/**
 * _getenv - searches the environment list to find the environment variable key
 *
 * @key: the environment variable
 *
 * Return: a pointer to value ,
 * or NULL if it doesn't exist
 */
char *_getenv(const char *key)
{
	char *value = NULL;
	int i = 0, j, k, equal, size;

	while (environ[i])
	{
		equal = 1;
		for (j = 0; environ[i][j] != '=' && key[j]; j++)
			if (key[j] != environ[i][j])
				equal = 0;
		if (equal && environ[i][j] == '=' && key[j] == '\0')
		{
			k = 0;
			for (size = j; environ[i][size]; size++)
				;
			size -= j;
			j++;

			value = (char *)malloc(sizeof(char) * (size + 1));
			if (value == NULL)
				exit(EXIT_FAILURE);
			while (environ[i][j])
			{
				value[k] = environ[i][j];
				k++;
				j++;
			}
			value[k] = '\0';
			break;
		}
		i++;
	}
	return (value);
}
