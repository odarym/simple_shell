#include "Shell.h"
#include "String.h"

/**
 * main - execve example
 *
 * @argc: number of arguments
 * @argv: argument vectors
 *
 * Return: Always 0.
*/
int main(int argc, char **argv)
{
	char *buffer, **array, c;
	int counter = 0;

	argc++; /* To fix argc is unsused compiler warnings */
	while (1)
	{
		counter++;
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);

		buffer = GetLine();

		c = buffer[0];

		if (c == '\0')
			continue;
		array = CommandParser(buffer);
		if (IsBuiltin(array[0]))
		{
			RunBuiltin(array, counter, argv[0]);
			free(array);
			free(buffer);
			continue;
		}
		else
			Execute(array, counter, argv, buffer);
		free(array);
		free(buffer);
	}
	return (0);
}


/**
*CommandParser- parses the commmand input
*
*@buffer: string containing command
*
*Return: Parsed command
*/
char **CommandParser(char *buffer)
{
	char **cmd, *token;
	int i = 0;

	if (!buffer)
		return (NULL);

	token = strtok(buffer, " \n");
	if (!token)
		return (NULL);

	cmd = malloc(sizeof(char *) * 1024);

	while (token)
	{
		cmd[i++] = token;
		token = strtok(NULL, " \n");
	}
	cmd[i] = NULL;
	return (cmd);
}


/**
* Execute - executes commands within the shell
*
* @array: parsed command
* @counter: command no
* @argv: commandline arguments
* @buffer:buffer containing input
*/
void Execute(char **array, int counter, char **argv, char *buffer)
{
	int status;

	if (fork() != 0)
	{
		wait(&status);
	}
	else
	{
		if (String_N_Compare(array[0], "./", 2) != 0 &&
			String_N_Compare(array[0], "/", 1) != 0)
		{
			SearchPath(&array[0]);
		}

		if (execve(*array, array, environ) == -1)
		{
			PrintErrorMessage(counter, array[0], argv[0]);
			free(array);
			free(buffer);
			exit(EXIT_FAILURE);
		}
	}
}

/**
* PrintErrorMessage - Print error message
*
* @counter: command no
* @cmd: command input
* @argv: commanline argument
*/
void PrintErrorMessage(int counter, char *cmd, char *argv)
{
	char *ptr;

	write(2, argv, StringLength(argv));
	write(2, ": ", 2);
	ptr = Itoa(counter);
	write(2, ptr, StringLength(ptr));
	write(2, ": ", 2);
	write(2, cmd, StringLength(cmd));
	write(2, ": not found\n", 12);
}
