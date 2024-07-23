#include "dupshell.h"

/**
 * cmd_exist - finds executable file in command
 * @d_typeinfo: the systeminfo struct
 * @path: denotes path of the file to be executed
 *
 * Return: 0 on code success, 1 if error
 */
int cmd_exist(d_type *d_typeinfo, char *path)
{
	struct stat st;

	(void)d_typeinfo;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_str - this function enables string duplication
 * @findpath: the env var PATH and its value
 * @indexstart: index of where to begin
 * @indexstop: index of where to indexstop
 *
 * Return: a pointer to buf declared
 */
char *dup_str(char *findpath, int indexstart, int indexstop)
{
	static char buf[1024];
	int j = 0, l = 0;

	for (l = 0, j = indexstart; j < indexstop; j++)
		if (findpath[j] != ':')
			buf[l++] = findpath[j];
	buf[l] = 0;
	return (buf);
}

/**
 * cmd_path - identify the PATH env var in string fetched
 * @d_typeinfo: struct of systeminfo
 * @findpath: env var PATH; string
 * @cmd: command from string to be found
 *
 * Return: NULL if command not found and it's path in full if found
 */
char *cmd_path(d_type *d_typeinfo, char *findpath, char *cmd)
{
	int j = 0, index = 0;
	char *path;

	if (!findpath)
		return (NULL);
	if ((str_len(cmd) > 2) && str_start(cmd, "./"))
	{
		if (cmd_exist(d_typeinfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!findpath[j] || findpath[j] == ':')
		{
			path = dup_str(findpath, index, j);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (cmd_exist(d_typeinfo, path))
				return (path);
			if (!findpath[j])
				break;
			index = j;
		}
		j++;
	}
	return (NULL);
}
