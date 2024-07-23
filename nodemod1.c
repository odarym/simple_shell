#include "dupshell.h"

/**
 * szlst - length of linked list
 * @hd: pointer to first nodePtr
 *
 * Return: size of list
 */
size_t szlst(const lst_t *hd)
{
	size_t k = 0;

	while (hd)
	{
		hd = hd->next_node;
		k++;
	}
	return (k);
}

/**
 * lsttostr - returns array of strings of the list->wrd
 * @start: first nodePtr pointer
 *
 * Return: array of strings
 */
char **lsttostr(lst_t *start)
{
	lst_t *nodePtr = start;
	size_t k = szlst(start), l;
	char **strPtr;
	char *string;

	if (!start || !k)
		return (NULL);
	strPtr = malloc(sizeof(char *) * (k + 1));
	if (!strPtr)
		return (NULL);
	for (k = 0; nodePtr; nodePtr = nodePtr->next_node, k++)
	{
		string = malloc(str_len(nodePtr->string) + 1);
		if (!string)
		{
			for (l = 0; l < k; l++)
				free(strPtr[l]);
			free(strPtr);
			return (NULL);
		}

		string = str_cpy(string, nodePtr->string);
		strPtr[k] = string;
	}
	strPtr[k] = NULL;
	return (strPtr);
}


/**
 * putlst - prints all elements lst_t
 * @hd: first nodePtr pointer
 *
 * Return: size of list
 */
size_t putlst(const lst_t *hd)
{
	size_t k = 0;

	while (hd)
	{
		_puts(stringify_no(hd->no, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->string ? hd->string : "(nil)");
		_puts("\n");
		hd = hd->next_node;
		k++;
	}
	return (k);
}

/**
 * specprefix - gives a nodePtr with prfx at the start of a string
 * @nodePtr: list head/start pointer
 * @prfx: string to match
 * @s: next char after prfx to match
 *
 * Return: match nodePtr or null
 */
lst_t *specprefix(lst_t *nodePtr, char *prfx, char s)
{
	char *q = NULL;

	while (nodePtr)
	{
		q = str_start(nodePtr->string, prfx);
		if (q && ((s == -1) || (*q == s)))
			return (nodePtr);
		nodePtr = nodePtr->next_node;
	}
	return (NULL);
}

/**
 * retrindex - retrives the index of a nodePtr
 * @start: list start/head pointer
 * @nodePtr: the nodePtr pointer
 *
 * Return: index of nodePtr or -1
 */
ssize_t retrindex(lst_t *start, lst_t *nodePtr)
{
	size_t k = 0;

	while (start)
	{
		if (start == nodePtr)
			return (k);
		start = start->next_node;
		k++;
	}
	return (-1);
}
