#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* Defines */
#define MAX_ARG 10
#define notUsed __attribute__((unused))
extern char **environ;

/* string functions */
int _putchar(char ch);
int _putstr(char *str);
int _strlen(char *str);
char **tokenize(void);
int countTokens(const char *str, const char *delim);
void readInput(char **line);

/* idk */
char *check_file(char *path);
int exe_command(char **arg);
int promt(void);

/* clean up functions */
void freeArg(char **args);

#endif
