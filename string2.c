#include "shell.h"
#include <unistd.h>

/**
 * _putnum - print unsigned integer
 *
 * @num: number to print
 *
 * Return: 0 (Always)
 */
int _putnum(unsigned int num)
{
	unsigned int cpy, i, cnt = 0;
	char str[] = "0000000000";

	cpy = num;
	while (cpy)
	{
		cnt++;
		cpy /= 10;
	}
	for (i = 0; num; i++)
	{
		str[cnt - i - 1] = '0' + num % 10;
		num /= 10;
	}
	if (!cnt)
		_putchar('0');
	else
		write(STDERR_FILENO, str, cnt);
	return (0);
}
/**
 * print_err - print error message to stderr
 *
 * @argv: ...
 * @count: ...
 * @av: ...
 * @prompt: ...
 *
 */
void print_err(char *argv, unsigned int count, char *av, char *prompt)
{
	_putstr(argv);
	_putchar(':'), _putchar(' ');
	_putnum(count);
	_putchar(':'), _putchar(' ');
	_putstr(av);
	_putchar(':'), _putchar(' ');
	_putstr(prompt);
}

/**
* _strcmp - compare two strings
*
* @a: first string
* @b: second string
*
* Return: 0 if they are the same else 1
*/
int _strcmp(char *a, char *b)
{
	int i;

	for (i = 0; a[i] && b[i]; i++)
		if (a[i] != b[i])
			return (1);
	if (a[i] || b[i])
		return (1);
	return (0);
}

/**
 * is_num - check if it's a number
 *
 * @num: the number
 *
 * Return: 1 if it's otherwise 0
 */
int is_num(char *num)
{
	int i;

	for (i = 0; num[i]; i++)
		if (num[i] < '0' || num[i] > '9')
			return (0);
	return (1);
}

/**
 * strToint - ...
 * @s: ...
 * Return: the int
 */
int strToint(char *s)
{
	int i, zero = 1, num = 0;

	for (i = 0; s[i]; i++)
		if (s[i] != '0')
		{
			zero = 0;
			break;
		}
	if (zero)
		return (0);
	for (i = 0; s[i]; i++)
	{
		num += (s[i] - '0');
		if (num)
			num *= 10;
	}
	num /= 10;
	return (num);
}
