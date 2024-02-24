#include "shell.h"
#include <unistd.h>

/**
 * _putcharout - print a char to stderr
 * @ch: char argument
 * Return: length
 */
int _putcharout(char ch)
{
	if (ch == '\0')
		return (0);
	return (write(STDOUT_FILENO, &ch, 1));
}

/**
 * _putstrout - print a string to stderr
 * @str: string argument
 * Return: length
 */
int _putstrout(char *str)
{

	if (!str)
		return (0);
	return (write(STDOUT_FILENO, str, _strlen(str)));
}
