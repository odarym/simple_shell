#include "Shell.h"

#include "String.h"


/**
 * SearchPath -  Search In $PATH For Excutable Command
 *
 * @cmd: Parsed Input
 *
 * Return: 1  Failure  0  Success.
 */
void SearchPath(char **cmd)
{
	char *path, *value, *cmd_path;
	struct stat buf;

	path = GetEnvironmentVariable("PATH");
	value = strtok(path, ":");
	while (value != NULL)
	{
		cmd_path = Build(*cmd, value);
		if (stat(cmd_path, &buf) == 0)
		{
			*cmd = StringDuplicate(cmd_path);
			free(cmd_path);
			break;
		}
		free(cmd_path);
		value = strtok(NULL, ":");
	}
	free(path);
}



/**
 * Build - Build Command
 * @token: Excutable Command
 * @value: Dirctory Conatining Command
 *
 * Return: Parsed Full Path Of Command Or NULL Case Failed
 */
char *Build(char *token, char *value)
{
	char *cmd;
	size_t len;

	len = StringLength(value) + StringLength(token) + 2;
	cmd = malloc(sizeof(char) * len);
	if (cmd == NULL)
	{
		return (NULL);
	}

	memset(cmd, 0, len);

	cmd = StringCat(cmd, value);
	cmd = StringCat(cmd, "/");
	cmd = StringCat(cmd, token);

	return (cmd);
}


/**
 * GetEnvironmentVariable - Gets The Value Of Enviroment Variable By Name
 * @name: Environment Variable Name
 * Return: The Value of the Environment Variable Else NULL.
 */
char *GetEnvironmentVariable(char *name)
{
	size_t nl, vl;
	char *value;
	int i, x, j;

	nl = StringLength(name);

	for (i = 0 ; environ[i]; i++)
	{
		if (String_N_Compare(name, environ[i], nl) == 0)
		{
			vl = StringLength(environ[i]) - nl;
			value = malloc(sizeof(char) * vl);
			if (!value)
			{
				free(value);
				perror("unable to alloc");
				return (NULL);
			}

			j = 0;
			for (x = nl + 1; environ[i][x]; x++, j++)
			{
				value[j] = environ[i][x];
			}
			value[j] = '\0';

			return (value);
		}
	}

	return (NULL);
}
