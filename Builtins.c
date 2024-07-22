#include "Shell.h"

#include "String.h"


/**
 * IsBuiltin - checks if command is a builtin command
 *
 * @command: command to check
 * Return: 0 if true, else -1
*/
bool IsBuiltin(char *command)
{
	int i = 0;
	char *array_cmd[] = {"exit", "env", "clear", NULL};

	while (array_cmd[i])
	{
		if (StringCompare(array_cmd[i], command) == 0)
			return (true);

		i++;
	}
	return (false);
}

/**
 * RunBuiltin - executes builtin commands
 * @command: command to execute
 * @counter: command no
 * @argv: argument vector
 * Return: 0 on success, -1 otherwise
 */

int RunBuiltin(char **command, int counter, char *argv)
{
	int i = 0;
	builtIn_t selector[] = {
		{"exit", Exit},
		{"env", GetEnvironment},
		{"clear", Clear},
		{NULL, NULL}
	};

	while ((selector + i)->command)
	{
		if (StringCompare((selector + i)->command, command[0]) == 0)
			return ((selector + i)->func(command, counter, argv));
		i++;
	}

	return (-1);
}

/**
 * Exit - exits the shell
 * @cmd: command
 * @counter: no command executed
 * @argv: argument vector
 * Return: 0 on success, -1 otherwise
 */
int Exit(char **cmd, int counter, char *argv)
{
	int i = 0, status = 0;
	char *ptr;

	if (!cmd[1])
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}

	while (cmd[1][i])
	{
		if (IsDigit(cmd[1][i]) == 0)
		{
			write(2, argv, StringLength(argv));
			write(2, ": ", 2);
			ptr = Itoa(counter);
			write(2, ptr, StringLength(ptr));
			write(2, ": ", 2);
			write(2, cmd[0], StringLength(cmd[0]));
			write(2, ": Illegal number: ", 18);
			write(2, cmd[1], StringLength(cmd[1]));
			write(2, "\n", 1);
			return (-1);
		}

		i++;
	}

	status = Atoi(cmd[1]);
	free(cmd);
	exit(status);
	return (0);
}

/**
 * GetEnvironment - prints the current environment
 * @cmd: command
 * @counter: command no
 * @argv: argument vector
 * Return: 0 on success, -1 otherwise
*/
int GetEnvironment(char **cmd, int counter, char *argv)
{
	int i = 0;
	(void)cmd;
	(void)counter;
	(void)argv;

	while (environ[i])
	{
		write(1, environ[i], StringLength(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}


/**
 * Clear - clears the terminal window
 * @cmd: command
 * @counter: command no
 * @argv: argument vector
 * Return: 0 on success, -1 otherwise
*/
int Clear(char **cmd, int counter, char *argv)
{
	(void)cmd;
	(void)counter;
	(void)argv;

	write(1, "\033[1;1H\033[2J", 10);

	return (0);
}
