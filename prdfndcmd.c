#include "dupshell.h"

/**
 * exitbin - this function indicates the exit of the custom shell
 * @d_typeinfo: struct potentially with args
 *          maintains constnt func prototype
 *
 *  Return: exits with 0 if d_typeinfo.argvstr[0] is != to exit
 */
int exitbin(d_type *d_typeinfo)
{
	int exitcheck;

	if (d_typeinfo->argvstr[1])
	{
		exitcheck = atoiErr(d_typeinfo->argvstr[1]);
		if (exitcheck == -1)
		{
			d_typeinfo->status = 2;
			outputErr(d_typeinfo, "Illegal number: ");
			output(d_typeinfo->argvstr[1]);
			putoutchar('\n');
			return (1);
		}
		d_typeinfo->error_no = atoiErr(d_typeinfo->argvstr[1]);
		return (-2);
	}
	d_typeinfo->error_no = -1;
	return (-2);
}

/**
 * cdbin - function that alters current directory
 * @d_typeinfo: struct that potentially has args
 *          maintain constnt func prototype
 *  Return: 0 on code execution success
 */
int cdbin(d_type *d_typeinfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!d_typeinfo->argvstr[1])
	{
		dir = retrienv(d_typeinfo, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = retrienv(d_typeinfo, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(d_typeinfo->argvstr[1], "-") == 0)
	{
		if (!retrienv(d_typeinfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(retrienv(d_typeinfo, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = retrienv(d_typeinfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(d_typeinfo->argvstr[1]);
	if (chdir_ret == -1)
	{
		outputErr(d_typeinfo, "can't cd to ");
		output(d_typeinfo->argvstr[1]), putoutchar('\n');
	}
	else
	{
		setenvset(d_typeinfo, "OLDPWD", retrienv(d_typeinfo, "PWD="));
		setenvset(d_typeinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpbin - function that alters current directory
 * @d_typeinfo: struct that potentially has args
 *          maintain cnstnt func prototype
 *  Return: 0 on code execution success
 */
int helpbin(d_type *d_typeinfo)
{
	char **arg_array;

	arg_array = d_typeinfo->argvstr;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
