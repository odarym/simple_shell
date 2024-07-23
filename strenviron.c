#include "dupshell.h"

/**
 * managenv - prints the current environment
 * @d_typeinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int managenv(d_type *d_typeinfo)
{
	printstrlst(d_typeinfo->envcpy);
	return (0);
}

/**
 * retrienv - gets the val of an environ variable
 * @d_typeinfo: Structure containing potential arguments. Used to maintain
 * @name: env varbl name
 *
 * Return: the val
 */
char *retrienv(d_type *d_typeinfo, const char *name)
{
	lst_t *node = d_typeinfo->envcpy;
	char *p;

	while (node)
	{
		p = str_start(node->string, name);
		if (p && *p)
			return (p);
		node = node->next_node;
	}
	return (NULL);
}

/**
 * modsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @d_typeinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int modsetenv(d_type *d_typeinfo)
{
	if (d_typeinfo->argc_no != 3)
	{
		output("Incorrect number of arguements\n");
		return (1);
	}
	if (setenvset(d_typeinfo, d_typeinfo->argvstr[1], d_typeinfo->argvstr[2]))
		return (0);
	return (1);
}

/**
 * unsetenvrm - Remove an environment variable
 * @d_typeinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetenvrm(d_type *d_typeinfo)
{
	int i;

	if (d_typeinfo->argc_no == 1)
	{
		output("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= d_typeinfo->argc_no; i++)
		rmsetenv(d_typeinfo, d_typeinfo->argvstr[i]);

	return (0);
}

/**
 * initenvar - populates env linked list
 * @d_typeinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initenvar(d_type *d_typeinfo)
{
	lst_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		putnode_end(&node, environ[i], 0);
	d_typeinfo->envcpy = node;
	return (0);
}
