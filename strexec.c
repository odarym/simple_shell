#include "dupshell.h"

/**
 * strexec - main shell loop
 * @d_typeinfo: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int strexec(d_type *d_typeinfo, char **av)
{
	ssize_t s = 0;
	int ret_def = 0;

	while (s != -1 && ret_def != -2)
	{
		resetinfo(d_typeinfo);
		if (modsys(d_typeinfo))
			_puts("$ ");
		putoutchar(FLUSH_INDICATOR);
		s = getSysInput(d_typeinfo);
		if (s != -1)
		{
			settinginfo(d_typeinfo, av);
			ret_def = search_builtin(d_typeinfo);
			if (ret_def == -1)
				search_cmd(d_typeinfo);
		}
		else if (modsys(d_typeinfo))
			_putchar('\n');
		memfrinfo(d_typeinfo, 0);
	}
	wrthist(d_typeinfo);
	memfrinfo(d_typeinfo, 1);
	if (!modsys(d_typeinfo) && d_typeinfo->status)
		exit(d_typeinfo->status);
	if (ret_def == -2)
	{
		if (d_typeinfo->error_no == -1)
			exit(d_typeinfo->status);
		exit(d_typeinfo->error_no);
	}
	return (ret_def);
}

/**
 * search_builtin - finds a builtin command
 * @d_typeinfo: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int search_builtin(d_type *d_typeinfo)
{
	int j, def_ret = -1;
	tblbuild modbuild[] = {
		{"exit", exitbin},
		{"env", managenv},
		{"help", helpbin},
		{"history", histdisp},
		{"setenv", modsetenv},
		{"unsetenv", unsetenvrm},
		{"cd", cdbin},
		{"alias", createaka},
		{NULL, NULL}
	};

	for (j = 0; modbuild[j].cmd; j++)
		if (str_cmp(d_typeinfo->argvstr[0], modbuild[j].cmd) == 0)
		{
			d_typeinfo->line_tt++;
			def_ret = modbuild[j].handler(d_typeinfo);
			break;
		}
	return (def_ret);
}

/**
 * search_cmd - finds a command in PATH
 * @d_typeinfo: the parameter & return info struct
 *
 * Return: void
 */
void search_cmd(d_type *d_typeinfo)
{
	char *path = NULL;
	int j, m;

	d_typeinfo->path = d_typeinfo->argvstr[0];
	if (d_typeinfo->counter_line == 1)
	{
		d_typeinfo->line_tt++;
		d_typeinfo->counter_line = 0;
	}
	for (j = 0, m = 0; d_typeinfo->argstr[j]; j++)
		if (!delimchar(d_typeinfo->argstr[j], " \t\n"))
			m++;
	if (!m)
		return;

	path = cmd_path(d_typeinfo, retrienv(d_typeinfo, "PATH="),
						d_typeinfo->argvstr[0]);
	if (path)
	{
		d_typeinfo->path = path;
		child_fork(d_typeinfo);
	}
	else
	{
		if ((modsys(d_typeinfo) || retrienv(d_typeinfo, "PATH=")
			|| d_typeinfo->argvstr[0][0] == '/')
							&& cmd_exist(d_typeinfo, d_typeinfo->argvstr[0]))
			child_fork(d_typeinfo);
		else if (*(d_typeinfo->argstr) != '\n')
		{
			d_typeinfo->status = 127;
			outputErr(d_typeinfo, "not found\n");
		}
	}
}

/**
 * child_fork - forks a an exec thread to run cmd
 * @d_typeinfo: the parameter & return info struct
 *
 * Return: void
 */
void child_fork(d_type *d_typeinfo)
{
	pid_t branch_pid;

	branch_pid = fork();
	if (branch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (branch_pid == 0)
	{
		if (execve(d_typeinfo->path, d_typeinfo->argvstr, strenv(d_typeinfo)) == -1)
		{
			memfrinfo(d_typeinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(d_typeinfo->status));
		if (WIFEXITED(d_typeinfo->status))
		{
			d_typeinfo->status = WEXITSTATUS(d_typeinfo->status);
			if (d_typeinfo->status == 126)
				outputErr(d_typeinfo, "Permission denied\n");
		}
	}
}
