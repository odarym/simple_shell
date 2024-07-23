#include "dupshell.h"

/**
 * strenv - arr of strings for environ is returned
 * @d_typeinfo: struct with args, mntn con func prototype
 *
 * Return: 0 on execution success
 */
char **strenv(d_type *d_typeinfo)
{
	if (!d_typeinfo->environcpy || d_typeinfo->altered_env)
	{
		d_typeinfo->environcpy = lsttostr(d_typeinfo->envcpy);
		d_typeinfo->altered_env = 0;
	}

	return (d_typeinfo->environcpy);
}

/**
 * rmsetenv - env varbl is eliminated
 * @d_typeinfo: struct with args, mntn con func prototype
 * @varbl: property of env variable string
 *
 * Return: 1 if rm success, 0 otherwise
 */
int rmsetenv(d_type *d_typeinfo, char *varbl)
{
	lst_t *nodePtr = d_typeinfo->envcpy;
	size_t i = 0;
	char *l;

	if (!nodePtr || !varbl)
		return (0);

	while (nodePtr)
	{
		l = str_start(nodePtr->string, varbl);
		if (l && *l == '=')
		{
			d_typeinfo->altered_env = rmnodeindex(&(d_typeinfo->envcpy), i);
			i = 0;
			nodePtr = d_typeinfo->envcpy;
			continue;
		}
		nodePtr = nodePtr->next_node;
		i++;
	}
	return (d_typeinfo->altered_env);
}

/**
 * setenvset - func to assgn val to new env varbl
 *             function to manipulate or mod already existing env varbl
 * @d_typeinfo: struct with args, mntn con func prototype
 * @varbl: property of the current env varbl string
 * @val: value
 *
 *  Return: 0 on code execution success
 */
int setenvset(d_type *d_typeinfo, char *varbl, char *val)
{
	char *buf = NULL;
	lst_t *nodePtr;
	char *l;

	if (!varbl || !val)
		return (0);

	buf = malloc(str_len(varbl) + str_len(val) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, varbl);
	str_cat(buf, "=");
	str_cat(buf, val);
	nodePtr = d_typeinfo->envcpy;
	while (nodePtr)
	{
		l = str_start(nodePtr->string, varbl);
		if (l && *l == '=')
		{
			free(nodePtr->string);
			nodePtr->string = buf;
			d_typeinfo->altered_env = 1;
			return (0);
		}
		nodePtr = nodePtr->next_node;
	}
	putnode_end(&(d_typeinfo->envcpy), buf, 0);
	free(buf);
	d_typeinfo->altered_env = 1;
	return (0);
}
