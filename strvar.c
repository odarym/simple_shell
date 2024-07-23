#include "dupshell.h"
/**
 * check_opp - checks if current char is a chain delimeter
 * @d_typeinfo: the parameter struct
 * @buf: char buffer
 * @s: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int check_opp(d_type *d_typeinfo, char *buf, size_t *s)
{
	size_t k = *s;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		d_typeinfo->buf_operation = OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		d_typeinfo->buf_operation = AND;
	}
	else if (buf[k] == ';')
	{
		buf[k] = 0;
		d_typeinfo->buf_operation = CHAIN;
	}
	else
		return (0);
	*s = k;
	return (1);
}

/**
 * chainproc - countinues the chain depending on the last status
 * @d_typeinfo: struct parameter
 * @buf: buffer char
 * @s: info on the current position in buf
 * @j: starting position in buf
 * @sz: length of buf
 *
 * Return: Void
 */
void chainproc(d_type *d_typeinfo, char *buf, size_t *s, size_t j, size_t sz)
{
	size_t k = *s;

	if (d_typeinfo->buf_operation == AND)
	{
		if (d_typeinfo->status)
		{
			buf[j] = 0;
			k = sz;
		}
	}
	if (d_typeinfo->buf_operation == OR)
	{
		if (!d_typeinfo->status)
		{
			buf[j] = 0;
			k = sz;
		}
	}

	*s = k;
}

/**
 * akasub - replaces aliases in the tokenized string
 * @d_typeinfo: the parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int akasub(d_type *d_typeinfo)
{
	int j;
	lst_t *nde;
	char *s;

	for (j = 0; j < 10; j++)
	{
		nde = specprefix(d_typeinfo->aka, d_typeinfo->argvstr[0], '=');
		if (!nde)
			return (0);
		free(d_typeinfo->argvstr[0]);
		s = str_chr(nde->string, '=');
		if (!s)
			return (0);
		s = str_dup(s + 1);
		if (!s)
			return (0);
		d_typeinfo->argvstr[0] = s;
	}
	return (1);
}

/**
 * varsub - substitutes vars in the tokenized string
 * @d_typeinfo: the parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int varsub(d_type *d_typeinfo)
{
	int j = 0;
	lst_t *nde;

	for (j = 0; d_typeinfo->argvstr[j]; j++)
	{
		if (d_typeinfo->argvstr[j][0] != '$' || !d_typeinfo->argvstr[j][1])
			continue;

		if (!str_cmp(d_typeinfo->argvstr[j], "$?"))
		{
			strsub(&(d_typeinfo->argvstr[j]),
				str_dup(stringify_no(d_typeinfo->status, 10, 0)));
			continue;
		}
		if (!str_cmp(d_typeinfo->argvstr[j], "$$"))
		{
			strsub(&(d_typeinfo->argvstr[j]),
				str_dup(stringify_no(getpid(), 10, 0)));
			continue;
		}
		nde = specprefix(d_typeinfo->envcpy, &d_typeinfo->argvstr[j][1], '=');
		if (nde)
		{
			strsub(&(d_typeinfo->argvstr[j]),
				str_dup(str_chr(nde->string, '=') + 1));
			continue;
		}
		strsub(&d_typeinfo->argvstr[j], str_dup(""));

	}
	return (0);
}

/**
 * strsub - replaces string
 * @prev: address of prev string
 * @next: next string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int strsub(char **prev, char *next)
{
	free(*prev);
	*prev = next;
	return (1);
}
