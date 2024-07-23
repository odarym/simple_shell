#include "dupshell.h"

/**
 * putnode_start - adds a node at the start of a list
 * @start: pointer to start node
 * @string: str field of node
 * @no: node ndx
 *
 * Return: size of list
 */
lst_t *putnode_start(lst_t **start, const char *string, int no)
{
	lst_t *newHd;

	if (!start)
		return (NULL);
	newHd = malloc(sizeof(lst_t));
	if (!newHd)
		return (NULL);
	filblock((void *)newHd, 0, sizeof(lst_t));
	newHd->no = no;
	if (string)
	{
		newHd->string = str_dup(string);
		if (!newHd->string)
		{
			free(newHd);
			return (NULL);
		}
	}
	newHd->next_node = *start;
	*start = newHd;
	return (newHd);
}
/**
 * putnode_end - adds a node at the end of a list
 * @start: address of pointer to start node
 * @string: string field of node
 * @no: node ndx
 *
 * Return: size of list
 */
lst_t *putnode_end(lst_t **start, const char *string, int no)
{
	lst_t *newHd, *nodePtr;

	if (!start)
		return (NULL);

	nodePtr = *start;
	newHd = malloc(sizeof(lst_t));
	if (!newHd)
		return (NULL);
	filblock((void *)newHd, 0, sizeof(lst_t));
	newHd->no = no;
	if (string)
	{
		newHd->string = str_dup(string);
		if (!newHd->string)
		{
			free(newHd);
			return (NULL);
		}
	}
	if (nodePtr)
	{
		while (nodePtr->next_node)
			nodePtr = nodePtr->next_node;
		nodePtr->next_node = newHd;
	}
	else
		*start = newHd;
	return (newHd);
}

/**
 * printstrlst - prints the string'th value of a list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t printstrlst(const lst_t *hd)
{
	size_t k = 0;

	while (hd)
	{
		_puts(hd->string ? hd->string : "(nil)");
		_puts("\n");
		hd = hd->next_node;
		k++;
	}
	return (k);
}

/**
 * rmnodeindex - removes a node at a given ndx
 * @start: address of pointer to first node
 * @ndx: ndx of node to remove
 *
 * Return: 1 success, 0 fail
 */
int rmnodeindex(lst_t **start, unsigned int ndx)
{
	lst_t *nodePtr, *prvnd;
	unsigned int k = 0;

	if (!start || !*start)
		return (0);

	if (!ndx)
	{
		nodePtr = *start;
		*start = (*start)->next_node;
		free(nodePtr->string);
		free(nodePtr);
		return (1);
	}
	nodePtr = *start;
	while (nodePtr)
	{
		if (k == ndx)
		{
			prvnd->next_node = nodePtr->next_node;
			free(nodePtr->string);
			free(nodePtr);
			return (1);
		}
		k++;
		prvnd = nodePtr;
		nodePtr = nodePtr->next_node;
	}
	return (0);
}

/**
 * memfree - frees all nodes
 * @hdptr: address of start node
 *
 * Return: void
 */
void memfree(lst_t **hdptr)
{
	lst_t *nodePtr, *next_node, *start;

	if (!hdptr || !*hdptr)
		return;
	start = *hdptr;
	nodePtr = start;
	while (nodePtr)
	{
		next_node = nodePtr->next_node;
		free(nodePtr->string);
		free(nodePtr);
		nodePtr = next_node;
	}
	*hdptr = NULL;
}
