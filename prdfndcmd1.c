#include "dupshell.h"

/**
 * histdisp - displays the history list
 * @d_typeinfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int histdisp(d_type *d_typeinfo)
{
	putlst(d_typeinfo->hist);
	return (0);
}

/**
 * rmaka - removes alias to string
 * @d_typeinfo: parameter struct
 * @string: the string alias
 *
 * Return:0 on success, 1 on error
 */
int rmaka(d_type *d_typeinfo, char *string)
{
	char *f, j;
	int rslt;

	f = str_chr(string, '=');
	if (!f)
		return (1);
	j = *f;
	*f = 0;
	rslt = rmnodeindex(&(d_typeinfo->aka),
		retrindex(d_typeinfo->aka, specprefix(d_typeinfo->aka, string, -1)));
	*f = j;
	return (rslt);
}

/**
 * setaka - sets alias to string
 * @d_typeinfo: parameter struct
 * @string: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int setaka(d_type *d_typeinfo, char *string)
{
	char *f;

	f = str_chr(string, '=');
	if (!f)
		return (1);
	if (!*++f)
		return (rmaka(d_typeinfo, string));

	rmaka(d_typeinfo, string);
	return (putnode_end(&(d_typeinfo->aka), string, 0) == NULL);
}

/**
 * printaka - prints an alias string
 * @nde: the alias nde
 *
 * Return: Always 0 on success, 1 on error
 */
int printaka(lst_t *nde)
{
	char *f = NULL, *a = NULL;

	if (nde)
	{
		f = str_chr(nde->string, '=');
		for (a = nde->string; a <= f; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(f + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * createaka - mimics the alias builtin (man alias)
 * @d_typeinfo: Structure containing potential arguments.
 *  Return: Always 0
 */
int createaka(d_type *d_typeinfo)
{
	int i = 0;
	char *f = NULL;
	lst_t *nde = NULL;

	if (d_typeinfo->argc_no == 1)
	{
		nde = d_typeinfo->aka;
		while (nde)
		{
			printaka(nde);
			nde = nde->next_node;
		}
		return (0);
	}
	for (i = 1; d_typeinfo->argvstr[i]; i++)
	{
		f = str_chr(d_typeinfo->argvstr[i], '=');
		if (f)
			setaka(d_typeinfo, d_typeinfo->argvstr[i]);
		else
			printaka(specprefix(d_typeinfo->aka, d_typeinfo->argvstr[i], '='));
	}

	return (0);
}
