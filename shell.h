#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>

/* Defines */
#define notUsed __attribute__((unused))

typedef struct {
	char *name;
	void (*func)(char **argv);
} buildin;

extern char **environ;

/* string functions */
int _putchar(char ch);
int _putstr(char *str);
int _putcharout(char ch);
int _putstrout(char *str);
int _strlen(char *str);
char **tokenize(int size);
int countTokens(const char *str, const char *delim);
char *readInput(int size);
void print_err(char *argv, unsigned int count, char *av, char *prompt);
int _strcmp(char *a, char *b);
int is_num(char *num);
int strToint(char *str);
int checkEmpty(char *line);

/* idk */
char *check_file(char *path);
int exe_command(char **arg, char *program_name, int count);
int prompt(void);
int check_exec(char *file);
void builtin_exit(char **arg, char *program_name, int err, int count);
char *_strdup(char *str);
char *_getenv(const char *key);
void env(char **args);
void _setenv(char **args);
void _unsetenv(char **args);
int checkBuild(char **args);



/* clean up functions */
void freeArg(char **args);

#endif
