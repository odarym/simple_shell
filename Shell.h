#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>

extern char **environ;
/**
 * struct BuiltIn - struct type defining a functiomn pointer to a command
 *
 * @command: command to execute
 * @func: A function pointer to execute a builtin command.
 */
typedef struct BuiltIn
{
	char *command;
	int (*func)(char **cmd, int counter, char *argv);
} builtIn_t;

char *GetEnvironmentVariable(char *name);
void SearchPath(char **cmd);
int RunBuiltin(char **command, int counter, char *argv);

int GetEnvironment(char **cmd, int counter, char *argv);
bool IsBuiltin(char *command);
int Clear(char **cmd, int counter, char *argv);
int Exit(char **cmd, int counter, char *argv);

void exec(char **cmd, int counter, char **argv);
char **CommandParser(char *buffer);
void PrintErrorMessage(int counter, char *cmd, char *argv);
void Execute(char **array, int counter, char **argv, char *buffer);

void RemoveComments(char *buff);
char *Build(char *token, char *value);
#endif
