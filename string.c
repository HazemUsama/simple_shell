#include "shell.h"

/**
 * _putchar - print a char to stderr
 * @ch: char argument
 * Return: length
 */
int _putchar(char ch)
{
	if (ch == '\0')
		return (0);
	return (write(STDERR_FILENO, &ch, 1));
}

/**
 * _putstr - print a string to stderr
 * @str: string argument
 * Return: length
 */
int _putstr(char *str)
{

	if (!str)
		return (0);
	return (write(STDERR_FILENO, str, _strlen(str)));
}

/**
 * _strlen - counnting string length
 * @str: string argument
 * Return: counter
 */
int _strlen(char *str)
{
	int count = 0;

	while (str  && str[count])
		count++;
	return (count);
}

/**
 * countTokens - count the number of tokens in a string
 *
 * @str: the string to count tokens in
 * @delim: the delimiter used to split the string into tokens
 *
 * Return: the number of tokens in the string
 */
int countTokens(const char *str, const char *delim)
{
	int count = 0;
	char *token, *str_copy = strdup(str);

	token = strtok(str_copy, delim);
	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}
	count++;
	free(str_copy);
	return (count);
}
