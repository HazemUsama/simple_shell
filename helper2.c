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

	while (__environ[i])
	{
		equal = 1;
		for (j = 0; __environ[i][j] != '=' && key[j]; j++)
			if (key[j] != __environ[i][j])
				equal = 0;
		if (equal)
		{
			k = 0;
			for (size = j; __environ[i][size]; size++)
				;
			size -= j;
			j++;

			value = (char *)malloc(sizeof(char) * (size + 1));
			if (value == NULL)
				exit(EXIT_FAILURE);
			while (__environ[i][j])
			{
				value[k] = __environ[i][j];
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

