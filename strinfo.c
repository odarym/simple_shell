#include "dupshell.h"

/**
 * resetinfo - initializes d_type struct
 * @d_typeinfo: struct address
 */
void resetinfo(d_type *d_typeinfo)
{
	d_typeinfo->argstr = NULL;
	d_typeinfo->argvstr = NULL;
	d_typeinfo->path = NULL;
	d_typeinfo->argc_no = 0;
}

/**
 * settinginfo - denotes struct named system
 * @d_typeinfo: & of struct; hexadecimal val
 * @av: argument vector; arg three
 */
void settinginfo(d_type *d_typeinfo, char **av)
{
	int j = 0;

	d_typeinfo->filename = av[0];
	if (d_typeinfo->argstr)
	{
		d_typeinfo->argvstr = tkzStr(d_typeinfo->argstr, " \t");
		if (!d_typeinfo->argvstr)
		{

			d_typeinfo->argvstr = malloc(sizeof(char *) * 2);
			if (d_typeinfo->argvstr)
			{
				d_typeinfo->argvstr[0] = str_dup(d_typeinfo->argstr);
				d_typeinfo->argvstr[1] = NULL;
			}
		}
		for (j = 0; d_typeinfo->argvstr && d_typeinfo->argvstr[j]; j++)
			;
		d_typeinfo->argc_no = j;

		akasub(d_typeinfo);
		varsub(d_typeinfo);
	}
}

/**
 * memfrinfo - system struct freed in fields
 * @d_typeinfo: &of struct
 * @total: checks if freeing total fields
 */
void memfrinfo(d_type *d_typeinfo, int total)
{
	freemem(d_typeinfo->argvstr);
	d_typeinfo->argvstr = NULL;
	d_typeinfo->path = NULL;
	if (total)
	{
		if (!d_typeinfo->buf_cmd)
			free(d_typeinfo->argstr);
		if (d_typeinfo->envcpy)
			memfree(&(d_typeinfo->envcpy));
		if (d_typeinfo->hist)
			memfree(&(d_typeinfo->hist));
		if (d_typeinfo->aka)
			memfree(&(d_typeinfo->aka));
		freemem(d_typeinfo->environcpy);
			d_typeinfo->environcpy = NULL;
		clearmem((void **)d_typeinfo->buf_cmd);
		if (d_typeinfo->rdfiledes > 2)
			close(d_typeinfo->rdfiledes);
		_putchar(FLUSH_INDICATOR);
	}
}
